""" Helper function for code c++ generator """


def read_content(file_path):
    """Returns content of a text file.   
    file_path: Give full path.
    """
    with open(file_path, 'rt', encoding='utf-8') as file:
        content = file.read()
        file.close()
        return content


def read_types(file_path):
    """ Returns a list of dictionaries of types.
    file_path: Give full path to types list file.
    """
    types = read_content(file_path).split()
    res = []
    i = 0
    while i < len(types):
        res.append({'raw': types[i], 'type': types[i+1]})
        i += 2
    return res
