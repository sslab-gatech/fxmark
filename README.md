FxMark: Filesystem Multicore Scalability Benchmark
==================================================

Install & build
---------------
- Tested: Ubuntu 14.04

- Install filesystem-specific packages (e.g., mkfs.*)
~~~~~~{.sh}
$ bin/install-fs-tools.sh
~~~~~~

- Build FxMark
~~~~~{.sh}
$  make
~~~~~

- Clean FxMark
~~~~~{.sh}
$  make clean
~~~~~


How to run
----------
- Benchmark configuration
    - Set target media paths at bin/run-fxmark.py (e.g., Runner.LOOPDEV)
    - Set configuration for each run at bin/run-fxmark.py (i.e., run_config)

- Run benchmark
    - A log file will be created at 'logs' directory with starting time.
~~~~~{.sh}
$  bin/run-fxmark.py
~~~~~


Plot results
----------
- Scalability graphs
~~~~~{.sh}
$  bin/plotter.py --ty sc --log {log file} --out {output pdf file}
~~~~~

- CPU utilization graphs
~~~~~{.sh}
$  bin/plotter.py --ty util --log {log file} --ncore {# core} --out {output pdf file}
~~~~~


Authors
-------
- Changwoo Min <changwoo@gatech.edu>
- Sanidhya Kashyap <sanidhya@gatech.edu>
- Steffen Maass <steffen.maass@gatech.edu>
- Taesoo Kim <taesoo@gatech.edu>
