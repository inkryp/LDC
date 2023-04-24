#/bin/sh
files=("A00828073" "A00828073_incremental" "A00828073_fails" "A00828073_variableDeclaredTwice")
for i in ${!files[@]}; do
  echo "Test Case #$(expr $i + 1)"
  CUR="./examples/${files[$i]}.toy"
  ./ldc.out < ${CUR}
  echo ""
done
