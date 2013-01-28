## Helper script for build_all.sh

FILE=$1
MACROS=$2

if [ "$FILE" = "" ]; then
  echo "Please provide filename to compile"
  exit
fi

echo "Compiling... [$FILE]"

if [ "$MACROS" = "" ];then
  g++ $FILE -o $FILE.bin
else
  g++ $FILE -o bin/$FILE.bin -D $MACROS
fi

echo "\tDONE! [./bin/$FILE.bin]"
