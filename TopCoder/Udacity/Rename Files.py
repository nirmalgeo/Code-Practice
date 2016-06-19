import os


def rename_files():
    output = os.listdir(r"D:\Code Practise\Udacity\New folder")
    current_path = os.getcwd()
    os.chdir(r"D:\Code Practise\Udacity\New folder")
    print (current_path)
    
    for file_name in output:
       print(file_name)
       os.rename(file_name, file_name.translate(None,"0123456789"))
                                                 
    
    

rename_files()
