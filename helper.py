""" Helper function for code c++ generator """


def read_content(file_path):
    """Returns content of a text file.
    file_path: Give full path.
    """
    with open(file_path, 'rt', encoding='utf-8') as file:
        content = file.read()
        file.close()
        return content


def write_content(file_path, content):
    """Write content to a text file.
    file_path: Give full path to types list file.
    content: String of text.
    """
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
        file.close()


def read_types(file_path):
    """Returns a list of dictionaries of types.
    file_path: Give full path to types list file.
    """
    types = read_content(file_path).split()
    res = []
    i = 0
    while i < len(types):
        res.append(
            {'raw': types[i], 'type': types[i+1], 'default': types[i+2]})
        i += 3
    return res
