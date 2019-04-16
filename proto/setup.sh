
mkdir cpp
path=./source
files=$(ls $path)
for filename in $files
do
   protoc -I=$path --cpp_out=./cpp $path/$filename
done
