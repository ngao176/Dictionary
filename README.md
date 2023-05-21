# Dictionary
This is a dictionary made in C. The dictionary.h header file is essentially our “interface” file, to use a more familiar Java analogy. This header file defines critical data types for our program and outlines the function interfaces that you need to implement.  The functions implemented in dictionary.c are then used by the driver sh.c to create the interactive command-line dictionary.

All the specifications for all the functions as comments in the dictionary.h header file.

sh.c implements the interactive shell with which we interface with the underlying data structure. The list of commands are recorded in the print_help() function in sh.c. 

Available shell commands:
(q)uit             Quit the dictionary.
(h)elp             Show this command guide.
(l)oad             Initialize an empty dictionary.
(l)oad [file]      Load a formatted dictionary file.
(s)how             Show all words in the dictionary.
(s)how [word]      Show the definition of a word.
showall            Show all words and their definitions.
(i)nsert word def  Insert a new word definition into dictionary.
                   Assume there will be no duplicate entries.
(r)emove word      Remove a word from the dictionary.
size               Show the size of the dictionary.

The load command
To begin, we need to load a dictionary file. You can use the load command like so:

(webster) l dict/short
Dictionary loaded with 5 word(s).
Alternatively, you can execute load without a dictionary file as argument, which will initialize an empty dictionary.

(webster) l
Dictionary loaded with 0 word(s).
Under the hood, the load command calls the load_dictionary function. If another dictionary has already been loaded, it would first call free_dictionary on that dictionary and then load the new one. The dictionary struct returned from the load_dictionary function is stored in a global variable in sh.c, so there can only be one loaded dictionary at a time. This command will not work right away, as it depends on the new_entry() and dict_insert_sorted() functions

