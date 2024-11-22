echo "##### CLEAN dbgen & qgen #####"
(cd dbgen; make clean)

echo "##### CLEAN data #####"
./9_clean.sh
