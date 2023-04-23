#/bin/sh
files=("A00828073" "A00828073_incremental" "A00828073_fails")
for i in ${!files[@]}; do
  # it=
  echo "Test Case #$(expr $i + 1)"
  CUR="./examples/${files[$i]}.toy"
  ./ldc.out < ${CUR}
done
# ./ldc.out < ./examples/A00828073.toy
# ./ldc.out < ./examples/A00828073_incremental.toy
# ./ldc.out < ./examples/A00828073_fails.toy