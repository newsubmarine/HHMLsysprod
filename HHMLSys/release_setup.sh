#Setup the release every time you log in

echo "Setting up all the things......."

cd ../

setupATLAS

cd ../build

asetup 21.2.182,AnalysisBase

source x86_64-*/setup.sh

cd ../hhmlsysprod/HHMLSys

echo -e "\033[1mdone!!!!\033[0m"
