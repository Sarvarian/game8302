""" Helper function for code c++ generator """

import os
import os.path


def read_content(file_path):
    """Returns content of a text file.
    file_path: Give a full path. (relative or absolute does not matter.)
    """
    with open(file_path, 'rt', encoding='utf-8') as file:
        content = file.read().strip()
        file.close()
        return content


def write_content(file_path, content):
    """Write content to a text file.
    file_path: Give a full path. (relative or absolute does not matter.)
    content: String of text.
    """
    with open(file_path, 'w', encoding='utf-8', newline='\n') as file:
        file.write(content)
        file.close()


def read_types(file_path):
    """Returns a list of dictionaries of types.
    file_path: Give full path to types list file. (relative or absolute does not matter.)
    """
    types = read_content(file_path).split()
    res = []
    i = 0
    while i < len(types):
        res.append(
            {'raw': types[i], 'type': types[i+1], 'default': types[i+2]})
        i += 3
    return res


def read_routine_templates(dir_path):
    """Returns a dictionary of types and their routines.
    dir_path: Give full path to routine template directory. (relative or absolute does not matter.)
    """
    names = os.listdir(dir_path)
    res = {}
    for name in names:
        path = os.path.join(dir_path, name)
        if os.path.isdir(path):
            continue
        name = name.removesuffix('.hpp')
        res[name] = read_content(path)
        res[name] = res[name].replace('\n', '\n\t')
        res[name] = res[name].replace('\n\t\n', '\n\n')
    return res
