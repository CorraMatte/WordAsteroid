import argparse
import multiprocessing as mp
import os
import random
import shutil
import string
import tarfile

NPROC = 10
ARCHIVE_DIR = os.path.abspath(os.path.join(os.pardir, 'archives'))
TMP_DIR = 'tmp'


def get_pass(string_length=10):
    letters = string.ascii_lowercase + string.digits
    return ''.join(
        random.choice(letters) for i in range(random.randint(4, string_length)))


def create_single_file(args):
    f = open('{}/tmp_{}.txt'.format(ARCHIVE_DIR, mp.current_process().pid), 'w')
    words = open('words.txt', 'r').read().splitlines()

    for i in range(500000):
        if i % 100 == 0:
            f.writelines('{}:{}\n'.format(args, get_pass()))
        f.writelines(
            '{}@testemail.it:{}\n'.format(words[i % len(words)], get_pass()))

    f.flush()


def create_archive(email):
    os.mkdir(TMP_DIR)
    p = mp.Pool(processes=10)
    args = [email for i in range(NPROC)]
    p.map(create_single_file, args)

    with tarfile.open('{}/archive_{}.tar.gz'.format(ARCHIVE_DIR,
                                                    mp.current_process().pid),
                      "w:gz") as tar:
        tar.add(TMP_DIR, arcname=os.path.basename(TMP_DIR))
        shutil.rmtree(TMP_DIR)


def main():
    parser = argparse.ArgumentParser(
        description='Create the archives for the game')
    parser.add_argument('-n', '--nfiles', type=int, default=4,
                        help='Number of file to be created')
    parser.add_argument('-e', '--email', required=True,
                        help='Email to create in order to be found during the game')
    args = parser.parse_args()
    nfiles = args.nfiles

    print("This program will be create {} of the size of 500MB each".format(
        nfiles))
    print("Continue?  [y/N]", end='')
    choose = input()

    if choose.upper() != 'Y':
        print("Nothing will be created")
        return

    print("Creating files..")

    for i in range(nfiles):
        print("Creating {}/{}".format(i + 1, nfiles))
        create_archive(args.email)

    print("Files creates")


if __name__ == '__main__':
    main()
