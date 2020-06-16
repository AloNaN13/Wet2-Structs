#!/bin/bash
if [[ -z $1 ]]; then
  echo to run type ./run_test.sh path_to_executable
  exit 15
fi

EXEC_PATH=$1
TEST_DIR="./tests/"
IN_DIR="${TEST_DIR}in/*"
OUT_DIR="${TEST_DIR}out/*"
TMP_DIR="${TEST_DIR}tmp/"
for f in $IN_DIR;
do
  F_NAME="$(basename -- $f)"
  ./${EXEC_PATH} < $f > ${TMP_DIR}out${F_NAME:2}
done
PASSED_ALL="TRUE"
MEM_ALL_PASSED="TRUE"
for f in $OUT_DIR;
do
  F_NAME="$(basename -- $f)"
  IN_FILE="${IN_DIR:0:-1}in${F_NAME:3}"
  diff_result=$(diff "${OUT_DIR:0:-2}/${F_NAME}" "${TMP_DIR}${F_NAME}")
  if [[ $diff_result != "" ]];
  then
    echo "${IN_FILE} FAILED"
    PASSED_ALL="FALSE"
  else
    echo "${IN_FILE} PASSED!"
  fi
  $(valgrind --error-exitcode=1 --leak-check=full --log-file="/dev/null" "./${EXEC_PATH}" < "${IN_FILE}" > /dev/null )
  if [[ $? -eq 0 ]];
  then
    echo "$IN_FILE MEM CHECK PASSED"
  else
    MEM_ALL_PASSED="FALSE"
    echo "$IN_FILE MEM CHECK FAILED FIX YOUR LEAKS..."
  fi
done
if [[ $PASSED_ALL == "TRUE" ]];
then
  echo "PASSED ALL TESTS HURRAY!"
fi
if [[ $MEM_ALL_PASSED == "TRUE" ]];
then
  echo "PASSED ALL MEM TESTS HURRAY!"
fi
if [[ $PASSED_ALL == "TRUE"  ]] && [[ $MEM_ALL_PASSED == "TRUE" ]];
then
  echo "
______  ___  _____ _____ ___________
| ___ \/ _ \/  ___/  ___|  ___|  _  \\
| |_/ / /_\ \ \`--.\ \`--.| |__ | | | |
|  __/|  _  |\`--. \\\`--. \  __|| | | |
| |   | | | /\__/ /\__/ / |___| |/ /
\_|   \_| |_|____/\____/\____/|___/

"
fi
#rm ./tests/tmp/*