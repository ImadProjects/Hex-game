#!/usr/bin/env bash
echo "."
echo ".."
echo "... im cleaning your sources"

echo "Running pre-commit hook"
echo "."
echo "."
echo "."

GSL_PATH=/opt/gsl-2.6 make && GSL_PATH=/opt/gsl-2.6 make test && GSL_PATH=/opt/gsl-2.6 make install

# $? stores exit value of the last command
if [ $? -ne 0 ]; then
echo "."
echo ".."

 echo "---> Le commit n'est pas possible si les tests échouent. Si vous voulez le faire quand meme ajouter l'option:"
 echo "git commit --no-verify -m '.....'"
 echo ".."
 echo "."

 exit 1
fi

make clean