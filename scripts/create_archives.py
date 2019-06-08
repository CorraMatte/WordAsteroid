import argparse
from datetime import datetime
import multiprocessing as mp
import os
import random
import shutil
import string
import tarfile

NPROC = 10
ARCHIVE_DIR = '/tmp'
TEMP_DIR = 'tmp'


def create_single_file(args):
    f = open('{}/tmp_{}.txt'.format(TEMP_DIR, mp.current_process().pid), 'w')
    words = open('email.txt', 'r').read().splitlines()
    pwds = open('password.txt', 'r').read().splitlines()

    for i in range(500):
        if i % 100 == 0:
            f.writelines('{}:{}'.format(args, pwds[i % len(pwds)]))
        f.writelines('{}@testemail.it:{}\n'.format(words[i % len(words)], pwds[i % len(pwds)]))

    f.flush()


def create_archive(email, archive_dir):
    if (not os.path.exists(TEMP_DIR)):
        os.mkdir(TEMP_DIR)
    p = mp.Pool(processes=10)
    args = [email for i in range(NPROC)]

    print("Creating the text files..")
    p.map(create_single_file, args)

    print("Creating the archive..")
    filename = '{}/archive_{}.tar.gz'.format(archive_dir, mp.current_process().pid)
    with tarfile.open(filename, "w:gz") as tar:
        tar.add(TEMP_DIR, arcname=os.path.basename(TEMP_DIR))
        shutil.rmtree(TEMP_DIR)

    return filename


def main():
    parser = argparse.ArgumentParser(description='Create the archives for the game')
    parser.add_argument('-n', '--nfiles', type=int, default=4, help='Number of file to be created')
    parser.add_argument('-e', '--email', required=True, help='Email to create in order to be found during the game')
    parser.add_argument('-d', '--dst', help='Archives destination folder', default='/tmp')
    args = parser.parse_args()
    nfiles = args.nfiles

    print("This program will be create {} of 400MB each".format(nfiles))
    print("Continue?  [y/N]", end='')
    choose = input()

    if choose.upper() != 'Y':
        print("Nothing will be created")
        return
    
    print("Creating archive")
    src = create_archive(args.email, args.dst)
    for i in range(nfiles - 1):
        t = int(datetime.now().timestamp())
        dst = '{}/archive_{}.tar.gz'.format(args.dst, t)
        shutil.copyfile(src, dst)

    print("Archive creates")


if __name__ == '__main__':
    main()
