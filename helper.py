""" Helper function for code c++ generator """


def read_content(file_path):
    """ Return content of a text file.
    file_path: Give full path.
    """
    with open(file_path, 'rt', encoding='str') as file:
        content = file.read()
        file.close()
        return content
