#/bin/sh
files=("original" "incremental" "fails" "variableDeclaredTwice" "test" "imposibleAssignment")
for i in ${!files[@]}; do
  echo "Test Case #$(expr $i + 1)"
  CUR="./examples/${files[$i]}.toy"
  ./ldc.out < ${CUR}
  echo ""
done
