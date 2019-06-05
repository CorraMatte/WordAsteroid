import argparse
import multiprocessing as mp
import os
import random
import shutil
import string
import tarfile

NPROC = 10
ARCHIVE_DIR = '/tmp/' # os.path.abspath(os.path.join(os.pardir, 'archives'))
TEMP_DIR = 'tmp'


def create_single_file(args):
    f = open('{}/tmp_{}.txt'.format(TEMP_DIR, mp.current_process().pid), 'w')
    words = open('email.txt', 'r').read().splitlines()
    pwds = open('password.txt', 'r').read().splitlines()

    for i in range(5000000):
        if i % 100 == 0:
            f.writelines('{}:{}'.format(args, pwds[i % len(pwds)]))
        f.writelines('{}@testemail.it:{}\n'.format(words[i % len(words)], pwds[i % len(pwds)]))

    f.flush()


def create_archive(email):
    if (!os.path.exists(TEMP_DIR)):
        os.mkdir(TEMP_DIR)
    p = mp.Pool(processes=10)
    args = [email for i in range(NPROC)]

    print("Creating the text files..")
    p.map(create_single_file, args)

    print("Creating the archive..")
    with tarfile.open('{}/archive_{}.tar.gz'.format(ARCHIVE_DIR, mp.current_process().pid), "w:gz") as tar:
        tar.add(TEMP_DIR, arcname=os.path.basename(TEMP_DIR))
        shutil.rmtree(TEMP_DIR)


def main():
    parser = argparse.ArgumentParser(description='Create the archives for the game')
    parser.add_argument('-n', '--nfiles', type=int, default=4, help='Number of file to be created')
    parser.add_argument('-e', '--email', required=True, help='Email to create in order to be found during the game')
    args = parser.parse_args()
    nfiles = args.nfiles

    print("This program will be create {} of 400MB each".format(nfiles))
    print("Continue?  [y/N]", end='')
    choose = input()

    if choose.upper() != 'Y':
        print("Nothing will be created")
        return
    
    for i in range(nfiles):
        print("Creating {}/{}".format(i + 1, nfiles))
        create_archive(args.email)

    print("Archive creates")


if __name__ == '__main__':
    main()
