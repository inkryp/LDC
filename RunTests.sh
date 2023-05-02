#/bin/sh
files=("original" "incremental" "fails" "variableDeclaredTwice" "test" "imposibleAssignment" "wrongIf" "simpleIf" "ifElse" "while" "fibonacci" "factorial")
for i in ${!files[@]}; do
  echo "Test Case #$(expr $i + 1) (${files[$i]})"
  CUR="./examples/${files[$i]}.toy"
  ./ldc.out < ${CUR}
  echo ""
done
