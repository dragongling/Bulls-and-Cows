from bs4 import BeautifulSoup
import requests


def download1(directory_path):
    hostname = 'https://www.morewords.com/unique-letters/'
    for word_length in range(6,8):
        file = open(directory_path + str(word_length) + '.txt', 'w')
        for letter in "abcdefghijklmnopqrstuvwxyz":
            print("Downloading " + str(word_length) + "-letter words on \"" + letter + "\"... ", end='')
            page = requests.get(hostname + str(word_length) + letter + '/')
            soup = BeautifulSoup(page.content, 'html.parser')
            words = soup.select('.main p a')
            for a in words:
                word = a.get_text()
                if len(word) == word_length and word[0] == letter:
                    file.write(word + '\n')
            print("Done!")
        file.close()
    print("Words downloaded successfully!")


def is_isogram(word):
    chars = set()
    for c in word:
        if c in chars:
            return False
        else:
            chars.add(c)
    return True


def download2(directory_path):
    hostname = "http://www.yougowords.com/speech/noun/"
    for word_length in range(5, 8):
        words = []
        print("Downloading " + str(word_length) + "-letter words...")
        print("Getting number of pages... ", end='')
        page = requests.get(hostname + str(word_length) + '-letters')
        soup = BeautifulSoup(page.content, 'html.parser')
        num_pages = int(soup.select('#wordBody .pagination ul li')[-1].select_one('a')['href'].split('-')[-1])
        print("Done!")

        for page_num in range(1, num_pages + 1):
            print("Downloading page " + str(page_num) + "/" + str(num_pages) + "... ", end='')
            page = requests.get(hostname + str(word_length) + '-letters-' + str(page_num))
            print("Extracting words... ", end='')
            soup = BeautifulSoup(page.content, 'html.parser')
            word_table = soup.select('#sortable-display tbody tr')
            for row in word_table:
                word_info = [x.get_text() for x in row.select('td')]
                words.append([word_info[0], word_info[4], word_info[5]])
            print("Done!")

        file_path = directory_path + str(word_length) + '.csv'
        print("Writing to '" + file_path + "'...", end='')
        file = open(file_path, 'w')
        for word_info in words:
            file.write(';'.join(word_info) + '\n')
        file.close()
        print("Done!")
    print("Words downloaded successfully!")


def read_csv(file_path):
    words_table = []
    with open(file_path, newline='\n') as file:
        for line in file:
            words_table.append(line.strip().split(';'))
    return words_table


def get_all_origins(words_table):
    origin_filters = set()
    for row in words_table:
        origin_filters.add(row[2])
    return origin_filters


def get_isograms(words_table, origin_filters):
    words = []
    for row in words_table:
        word = row[0].lower()
        if row[2] in origin_filters and is_isogram(word):
            words.append(word)
    return words


directory = 'data/yougowords.com/Tables/'
file_path = directory + str(7) + '.csv'
print('\n'.join(sorted(get_isograms(read_csv(file_path), {'Middle English'}))))