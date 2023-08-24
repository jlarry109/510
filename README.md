# FinTech510 Student Repository

This repository provides the notebookes used for the FinTech 510 - Programming for Financial Technology course at Duke University.

## Getting started
As presented in the environment installation instructions, you should create a private fork of this repository and then clone to your local machine.  We assume you have created a "fintech510" directory in your home directory and have cloned your repository to that directory.

To create a local environment for programming and to execute the python notebooks, execute the following commands in terminal window:
```
cd ~/fintech510
python3.11 -m venv/class
source classenv/bin/activate
pip install --upgrade pip setuptools wheel
pip install -r fintech510-studentrepository/notebooks/requirements.txt
```
This creates and activates a Python virtual environment within installed libraries specifi to just this class.

If you close your terminal window, you will need to execute
```
source ~/fintech510/class/bin/activer
```
to activate the environment.
## Starting the notebooks
Once you have activiated the course environment, execute the following to start the Juypyter notebook server.
```
cd ~fintech510/fintech510-studentrepository/notebooks
jupyter notebook
```
