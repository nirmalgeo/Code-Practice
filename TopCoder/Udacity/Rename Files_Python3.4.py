import os
import string


def rename_files():
    output = os.listdir(r"D:\Code Practise\Udacity\New folder")
    current_path = os.getcwd()
    os.chdir(r"D:\Code Practise\Udacity\New folder")
    print (current_path)

    inputtab = " "
    outputtab = "1"
    table = str.maketrans(outputtab, inputtab)
    
    for file_name in output:
        os.rename(file_name, file_name.translate(table))
        os.rename(file_name, file_name.replace("a",""))

    print (output)
 
 
                                                 
    
    

rename_files()
