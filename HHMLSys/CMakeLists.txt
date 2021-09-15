# Declare the package name:
atlas_subdir( HHMLSys )

# Declare the package dependencies:
atlas_depends_on_subdirs( PUBLIC
                   	  PhysicsAnalysis/MCTruthClassifier
			  Tools/PathResolver
                          AsgTools )

# This package uses ROOT:
find_package( ROOT COMPONENTS Core Tree Hist Gpad RIO TMVA )

# Build a library that other components can link against:
atlas_add_library( HHMLSysLib
                   HHMLSys/*.h Root/*.cxx
                   PUBLIC_HEADERS HHMLSys
		   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES}
		   		  MCTruthClassifierLib
		   		  AsgTools
				  PathResolver )

atlas_add_dictionary( HHMLSysDict
		      HHMLSys/HHMLSysDict.h
		      HHMLSys/selection.xml
		      LINK_LIBRARIES HHMLSysLib )

# Build executable target
atlas_add_executable( runHHMLSys 
		      util/runHHMLSys.cxx
   		      LINK_LIBRARIES HHMLSysLib )

# Install data files from the package:
atlas_install_data( DIRECTORY data )

