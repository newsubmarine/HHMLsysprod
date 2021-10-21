#!/usr/bin/env python

#
# Script for submitting the HTCondor jobs
#

import os
import sys
import subprocess
import time
import logging
import collections

from optparse import OptionParser
p = OptionParser()

p.add_option('--output', '-o',  type='string',  default=None ,  dest='output')
p.add_option('--dir-path'    ,  type='string',  default=None ,  dest='dir_path')
p.add_option('--input-files' ,  type='string',  default=None ,  dest='input_files')
p.add_option('--afs-path'    ,  type='string',  default=None ,  dest='afs_path')
p.add_option('--configFile'  ,  type='string',  default=None ,  dest='configFile')
p.add_option('--mcRun'       ,  type='string',  default=None ,  dest='mcRun')
p.add_option('--txtFilesDir' ,  type='string',  default=None ,  dest='txtFilesDir')

p.add_option('--mb-per-job',    type='int',     default=1000,  dest='mb_per_job')
p.add_option('--nprint', '-p',  type='int',     default=1,     dest='nprint')

p.add_option('--debug', '-d',     action='store_true', default=False, dest='debug')
p.add_option('--make-job-dir',    action='store_true', default=False, dest='make_job_dir')
p.add_option('--submit', '-s',    action='store_true', default=False, dest='submit')


(options, args) = p.parse_args()

#======================================================================================================        
def getLog(name, level='INFO', debug=False, print_time=False):

    if print_time:
        f = logging.Formatter('%(asctime)s %(name)s %(levelname)s %(message)s', datefmt='%H:%M:%S')
    else:
        f = logging.Formatter('%(name)s: %(levelname)s - %(message)s')
        
    sh = logging.StreamHandler(sys.stdout)
    sh.setFormatter(f)
    
    fh = logging.FileHandler('job.log')
    fh.setFormatter(f)

    log = logging.getLogger(name)
    log.addHandler(sh)
    log.addHandler(fh)
    
    if debug:
        log.setLevel(logging.DEBUG)
    else:
        if level == 'DEBUG':   log.setLevel(logging.DEBUG)
        if level == 'INFO':    log.setLevel(logging.INFO)
        if level == 'WARNING': log.setLevel(logging.WARNING)    
        if level == 'ERROR':   log.setLevel(logging.ERROR)

    return log

log = getLog('sub_Condor.py', print_time=False)

#======================================================================================================
class Pushd:

    init_dir = None
    orig_dir = None

    def __init__(self, dirname):
        self.init_dir = os.path.realpath(dirname)
        self.orig_dir = None
        
    def __enter__(self):
        self.orig_dir = os.getcwd()
        os.chdir(self.init_dir)

        log.debug('Pushd.__enter__ - CWD=%s' %os.getcwd())
        return self
 
    def __exit__(self, type, value, tb):
        os.chdir(self.orig_dir)
        log.debug('Pushd.__exit__ - CWD=%s' %os.getcwd())

#======================================================================================================
def createJobScript(files, outDir, jobKey):

    if not os.path.isdir(outDir):
        raise Exception('createJobScript - invalid out directory: %s' %outDir)
        
    if not options.afs_path:
        log.error('createJobScript - afs path to save log/err files is not given: %s' %jobKey)
        sys.exit(1)

    if not os.path.isdir(options.afs_path):
        os.makedirs(options.afs_path)

    if not os.path.isfile(options.configFile):
        log.error('createJobScript - config file %s not found' %options.configFile)
        sys.exit(1)

    if not options.mcRun:
        log.error('createJobScript - mc campaign is not given: %s' %options.mcRun)
        sys.exit(1)

    if not (options.mcRun == "mc16a" or options.mcRun == "mc16e" or options.mcRun == "mc16d"):
        log.error('createJobScript - Wrong mc campaign %s, mcRun should be either mc16a or mc16d or mc16e' %options.mcRun)
        sys.exit(1)

    jobScript = 'job_%s.sh' %jobKey
    jobResult = '%s/job_%s' %(options.afs_path, jobKey)

    if os.path.isfile('%s.fail' %jobResult):
        log.error('createJobScript - please clean up aborted job: %s.fail' %jobResult)
        sys.exit(1)

    if os.path.isfile('%s.pass' %jobResult):
        log.info('createJobScript - skip successfully completed job: %s' %jobKey)
        return None

    #Job options
    jobOpts = '--sp %s --conf %s --mcRun %s '%(files, options.configFile, options.mcRun)

    stext = '#!/bin/sh\n\n'

    #Setup env.
    stext += 'export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase \n'
    stext += 'source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh \n\n'

    stext += 'pwd=$PWD \n'
    stext += 'echo pwd \n\n'
    stext += 'lsetup asetup \n'
    stext += 'cd /publicfs/atlas/atlasnew/higgs/HHML/Slim_sys_prod/build/ \n'
    stext += 'asetup 21.2.182,AnalysisBase \n'
    stext += 'source x86_64-*/setup.sh \n'
    stext += 'cd pwd \n\n'

    #Check if file is copied or not. If not read the file directly. (wip: copy only the large files?)
    stext += 'echo Reading %s.root file directly'%files + '\n'
    stext += ' %s\n\n' %(' '.join(['runHHMLSys', jobOpts]))
    
    #Check if job succeeded or failed. Then, copy the output root file to output directory and delete the input file.
    stext += 'job_return_code=$?\n\n'

    stext += 'if [ $job_return_code -ne 0 ]\n'
    stext += 'then\n'
    stext += '   touch %s.fail\n' %jobResult
    stext += '   echo job command has failed with code=$job_return_code - quit job now...\n'
    stext += '   exit $job_return_code\n'
    stext += 'else\n'
    stext += '    ls -lah %s.root'%jobKey + '\n'
    stext += '    lsFail=$? \n'
    stext += '    if [ $lsFail -ne 0 ]\n'
    stext += '    then\n'
    stext += '        echo %s.root not found'%jobKey + '\n'
    stext += '        touch %s.fail\n' %jobResult 
    stext += '    else\n'
    stext += '        echo copying the output file to output dir....\n'
    stext += '        xrdcp -np -f '+ '%s.root '%jobKey + '%s/%s.root'%(outDir, jobKey) + '\n'
    stext += '        fileCopyToDir=$? \n'
    stext += '        if [ $fileCopyToDir -ne 0 ] \n'
    stext += '        then\n'  
    stext += '            echo %s.root couldnt copy to dir.'%jobKey + ' I/O error ?? Ok lets try to mv it to afs area... \n'
    stext += '            mv '+ '%s.root '%jobKey + '%s'%options.afs_path + '\n'
    stext += '            fileCopyToafs=$? \n'
    stext += '            if [ $fileCopyToafs -ne 0 ] \n'
    stext += '            then\n'
    stext += '                echo %s.root couldnt copy to afs'%jobKey + '\n'
    stext += '                touch %s.fail\n' %jobResult
    stext += '            else\n'
    stext += '                touch %s.pass\n' %jobResult
    stext += '                echo Done!!!!\n'
    stext += '            fi \n'
    stext += '        else\n'
    stext += '            touch %s.pass\n' %jobResult
    stext += '            echo deleting the output root file....\n'
    stext += '            rm -r %s.root '%jobKey + ' \n'
    stext += '            echo All Done!!!!\n'
    stext += '        fi \n'
    stext += '    fi \n'
    stext += 'fi \n\n'

    sfile = open('%s/%s' %(options.afs_path, jobScript), 'w')
    sfile.write(stext)
    sfile.close() 

    return jobScript 
    
#======================================================================================================
def prepareFilesFromTxt(file_list, SampleID):

    files = []

    if not os.path.isfile(file_list):
        log.warning('Input file path is not valid: %s' %file_list)
        return files

    ifile = open(file_list, 'r')

    log.info('Read file list from: %s' %file_list)

    #
    # Select input files 
    #
    for line in ifile.readlines():
        
        #All the systematic root files are on IHEP.
        if not line.startswith('/publicfs/atlas/atlasnew/higgs/HHML/'):
            raise Exception('prepareFilesFromTxt - unknown sys. root file: ' %line)
            
        files += [(line.rstrip().strip(), SampleID)]

    return files

#======================================================================================================
def filelen(file):
    with open(file) as f:
        for i, l in enumerate(f):
            pass

    return i + 1

#======================================================================================================
def prepJobFiles(files):

    jobFiles = []
    curFiles = []
    curSize  = 0
    curID    = []
    maxSize  = options.mb_per_job*1048576

    for ifile, idfile in files:

        if type(ifile) != str or type(idfile) != str:
            log.warning('Invalid file: %s' %ifile)
            continue

        if not os.path.isfile(ifile):
            log.warning('Skip non existing file: %s' %ifile)
            continue
            
        ifile_path = ifile
        ifile_size = os.path.getsize(ifile)
        ifile_ID   = idfile

        #One file per job. To make life easier.
        nfile_per_job = 1
        pass_count = (nfile_per_job > 0 and len(curFiles) + 1 >= nfile_per_job)
        pass_size  = (options.mb_per_job > 0 and curSize + ifile_size >  maxSize)

        if pass_count or pass_size:
            add_curr = False
            
            if options.mb_per_job == 0:
                add_curr = True
            else:
                if curSize <= int(0.1*maxSize):
                    add_curr = True
                elif float(curSize + ifile_size)/max(float(curSize), maxSize) < 1.2:
                    add_curr = True

            if add_curr:
                curFiles += [ifile_path]
                curSize  += ifile_size
                curID    += [ifile_ID]

            jobFiles += [(curFiles, curSize, curID)]
            curFiles = []
            curSize  = 0
            curID    = []

            if add_curr:
                curFiles = []
                curSize  = 0
                curID    = []
            else:
                curFiles = [ifile_path]
                curSize  = ifile_size
                curID    = [ifile_ID]
        else:
            curFiles += [ifile_path]
            curSize  += ifile_size
            curID    += [ifile_ID]

    if len(curFiles):            
        jobFiles += [(curFiles, curSize, curID)]

    return jobFiles

#======================================================================================================
def printOut(target, value):

    if len(value.strip()):
        target.write(value)
        target.flush()

#======================================================================================================
def procJob(files, file_sizes, outDir, jobKey):

    file_sizes_mb = int(float(file_sizes)/1048576.0)

    #
    # Create Condor submit script and prepare submission
    #
    jobPrint      = (ijob % options.nprint == 0)
    jobOutput     = 'job_%s.out' %jobKey
    jobError      = 'job_%s.err' %jobKey
    #jobLog        = 'job_%s.log' %jobKey

    jobScript = createJobScript(files, outDir, jobKey)

    if jobScript == None:
        return

    jobResult = '%s' %options.afs_path
        
    #Use the appropriate mem usage depending on the file size.
    #If file size is < 2 Gb. Use the default 1Gb.
    #If file size is > 2 Gb and < 10 Gb. Use the 3Gb.
    #If file size is > 10 Gb. Use the 5Gb.
    
    memory = 1000

    if file_sizes_mb >= 2000 and file_sizes_mb <= 10000:
        memory = 3000
    elif file_sizes_mb > 1e4:
        log.info('Request for more disk/memory resources for file > 10 Gb')
        memory = 5000    
    else:
        log.info('Input file size is <2 Gb. 1Gb memory request is made')

    commands = ['hep_sub', '-o %s'%(jobResult + '/' + jobOutput), '-e %s'%(jobResult + '/' + jobError), '-mem %s'%memory, jobScript]
        
    ostr = 'job {} using file {} with size {} MB: {}'.format(ijob, jobKey, file_sizes_mb, ' '.join(commands))
    
    if options.submit:
        #process  = subprocess.Popen(commands, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        commandsShellTrue = ' '.join(commands)
        process  = subprocess.Popen(commandsShellTrue, stdout=subprocess.PIPE, stderr=subprocess.PIPE,shell=True,cwd=options.output)

        (stdout, stderr) = process.communicate()
            
        if jobPrint:
            log.info('Submitted %s' %ostr)
            printOut(sys.stdout, stdout)
            printOut(sys.stderr, stderr)
    else:
        if jobPrint:
            log.info('Prepared %s' %ostr)

    return jobScript
    
#======================================================================================================
if __name__ == '__main__':

    if options.output == None:
        log.error('Need output option - path to output directory')
        sys.exit(1)
        
    if not os.path.isdir(options.output):
        os.makedirs(options.output)

    timeStart = time.time()
    
    files = []
    
    txtfilesDir = '%s' %options.txtFilesDir
    
    #Check if the dir. containing .txt files exist
    if not os.path.isdir(txtfilesDir):
        raise Exception('main - invalid directory containing txt files: %s' %txtfilesDir)

    for txtfiles in sorted(os.listdir(txtfilesDir)):

        #Check non txt files
        if not txtfiles.endswith(".txt"):
            log.warning('Skip non-txt file: %s' %txtfiles)
            continue

        #Full path of input txt files
        input_file = '%s/%s'%(txtfilesDir, txtfiles)

        #Check the txt file size is non-zero
        if os.path.getsize(input_file) == 0:
            log.warning('Skip non-existing txt file: %s' %input_file)
            continue

        #Each txt file starts with ID of corresponding root file. 
        try:
            fileid   = txtfiles.index('_')
            sampleID = txtfiles[:fileid]
            
            if sampleID == 0:
                raise Exception('main - sample ID is zero. Something went wrong!')
        except:
            raise Exception('main - Couldn''t extract the sample ID. Something went wrong!')

        #Filter out priority 1 samples
        if sampleID not in {'450661', '450662', '450663',
                            '413008',
                            '410156', '410157', '410218', '410219', '410220',
                            '410470',
                            '410472',
                            '345873', '345874', '345875',
                            '410560',
                            '364250', '364253', '364254', '364255', '364283', '364284', '364285', '364286', '364287', 
                            '363355', '363356', '363357', '363358', '363359', '363360', '363489',
                            '364242', '364243', '364244', '364245', '364246', '364247', '364248', '364249', 
                            '364500', '364501', '364502', '364503', '364504', '364505', '364506', '364507', '364508', '364509',
                            '364510', '364511', '364512', '364513', '364514', '364521', '364522', '364523', '364524', '364525', 
                            '364526', '364527', '364528', '364529', '364530', '364531', '364532', '364533', '364534', '364535',
                            '342284', '342285',
                            '361106', '361107',
                            '364100', '364101', '364102', '364103', '364104', '364105', '364106', '364107', '364108', '364109',
                            '364110', '364111', '364112', '364113', '364114', '364115', '364116', '364117', '364118', '364119',
                            '364120', '364121', '364122', '364123', '364124', '364125', '364126', '364127', '364128', '364129',
                            '364130', '364131', '364132', '364133', '364134', '364135', '364136', '364137', '364138', '364139',
                            '364140', '364141',
                            '364156', '364157', '364158', '364159', '364160', '364161', '364162', '364163', '364164', '364165',
                            '364166', '364167', '364168', '364169', '364170', '364171', '364172', '364173', '364174', '364175',
                            '364176', '364177', '364178', '364179', '364180', '364181', '364182', '364183', '364184', '364185',
                            '364186', '364187', '364188', '364189', '364190', '364191', '364192', '364193', '364194', '364195', '364196', '364197',
                            '364198', '364199', '364200', '364201', '364202', '364203', '364204', '364205', '364206', 
                            '364207', '364208', '364209', '364210', '364211', '364212', '364213', '364214', '364215',
                            '304014',
                            '410080',
                            '410082',
                            '700011', '700012', '700013', '700014', '700015', '700016', '700017'}:
            continue

        #Make sure the .txt file contain at least one root file
        if filelen(input_file) < 1:
            log.error('Input file list is empty: %s' %input_file)
            sys.exit(1)

        #Read root files from .txt
        if os.path.isfile(input_file):
            files += prepareFilesFromTxt(input_file, sampleID)
        else:
            log.warning('Skip non-existing input file: %s' %input_file)
    
    if len(files) == 0:
        log.error('Failed to find matching input files... nothing to do')
        sys.exit(1)

    #
    # Make input file list for each job
    #
    log.info('Number of selected root files: %d' %len(files))
    
    jobFiles = prepJobFiles(files)
    
    if len(jobFiles) == 0:
        log.info('No valid files available to build jobs... nothing to do')
        sys.exit(0)

    #
    # Prepare submission command 
    #
    jobPath  = '%s' %(options.output.rstrip('/'))
   
    #
    # Create jobs
    #
    log.info('Output directory: %s' %options.output)
    if options.afs_path:
        log.info('AFS directory for log/err/out files: %s' %options.afs_path)
    log.info('Will prepare %d job(s)' %len(jobFiles))

    countJob   = 0
    countFile  = 0
    jobScripts = []
    prevjobKey = 0
    
    count = 0

    for ijob in range(0, len(jobFiles)):

        input_file_list    = jobFiles[ijob][0]
        input_file_size    = jobFiles[ijob][1]
        input_file_ID_list = jobFiles[ijob][2]

        if not (input_file_list or input_file_ID_list):
            log.info('No valid file or file ID is available to build jobs... nothing to do')
            sys.exit(0)
            
        jobKey = '%s' %(input_file_ID_list[0])

        if( prevjobKey == jobKey ):
            count += 1
            jobKey = '%s_part%d' %(input_file_ID_list[0], count)
        else:
            prevjobKey = jobKey
            count = 0

        if options.make_job_dir:
            jobDir = '%s/job_%s' %(jobPath, jobKey)
        else:
            jobDir = '%s'%(jobPath)
            
        if not os.path.isdir(jobDir):
            os.makedirs(jobDir)

        if not input_file_list[0].count('root'):
            log.error('Input file is not a root file: %s' %input_file_list[0])
            break
            
        with Pushd(jobDir):
            jobScripts += [procJob(input_file_list[0], input_file_size, jobDir, jobKey)]

        countJob  += 1    
        countFile += len(input_file_list)
        
    print
    log.info('Processed %d jobs and %d files - all is done' %(countJob, countFile))
    log.info('Local time: %s'    %time.asctime())
    log.info('Total time: %.1fs' %(time.time()-timeStart))
