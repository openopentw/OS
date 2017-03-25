# you should add sudo to run this script
# then the script will copy the files below to the correct position
# you can also add any file you want to copy in this script
cp syscall_table_32.S /usr/src/linux-2.6.32.60/arch/x86/kernel/
cp -r asm /usr/src/linux-2.6.32.60/arch/x86/include/
cp -r kernel/ /usr/src/linux-2.6.32.60/
