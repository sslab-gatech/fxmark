#!/usr/bin/env python3
import fileinput
import os
import sys
import signal
import subprocess
import datetime
import tempfile
import pdb

name_map = {
    "n_blk_wrt":"DWOL",
    "n_mtime_upt":"DWOM",
    "n_blk_alloc":"DWAL",
    "u_file_tr":"DWTL",
    "n_jnl_cmt":"DWSL",
    "n_file_rd":"DRBL",
    "n_shfile_rd":"DRBM",
    "n_shblk_rd":"DRBH",
    "n_inode_alloc":"MWCL",
    "u_file_cr":"MWCM",
    "u_sh_file_rm":"MWUL",
    "u_file_rm":"MWUM",
    "n_file_rename":"MWRL",
    "n_dir_ins":"MWRM",
    "n_path_rsl":"MRPM",
    "n_spath_rsl":"MRPH",
    "n_dir_rd":"MRDL",
    "n_shdir_rd":"MRDM",
    "n_file_rd_bg":"DRBL_bg",
    "n_shfile_rd_bg":"DRBM_bg",
    "n_shblk_rd_bg":"DRBH_bg",
    "n_dir_rd_bg":"MRDL_bg",
    "n_shdir_rd_bg":"MRDM_bg",
    "n_path_rsl_bg":"MRPM_bg",
}


if __name__ == "__main__":
    filename = sys.argv[1]
    for line in fileinput.input(filename, inplace = 1):
        for old in name_map:
            new = name_map[old]
            line = line.replace(old, new)
        print(line, end="")
