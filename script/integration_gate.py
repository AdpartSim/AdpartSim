import os, sys, glob, shutil
from dotenv import load_dotenv

# get the root path
ret = 0
root_path = os.path.abspath(os.path.dirname(sys.argv[0]) + "/../")
workflow_path = os.path.abspath(f"{root_path}/adpart_sim")

# copy AdpartSim bin to the path
os.system(f"mkdir -p {workflow_path}")
shutil.copy(f"{root_path}/build/AdpartSim", f"{workflow_path}/AdpartSim")


if not load_dotenv(f"{root_path}/.env", override=True):
    print(f"load .env error, skip it: {root_path}/.env")

# get all testcase configure
config_files = glob.glob(f"{root_path}/example/testcase/*.json")
for config_file in config_files:
    if "workload/" not in config_file:
        config_name = ".".join(os.path.basename(config_file).split(".")[:-1])
        print("-" * 50)
        bin_path = f"{workflow_path}/AdpartSim"
        output_path = f"{workflow_path}/result/{config_name}"
        ret += os.system(f"{bin_path} --input={config_file} --output={output_path}")
        ret += os.system(f"python3 {root_path}/script/draw_result.py {output_path}")
    if ret > 0:
        print("test failed")
        exit()

# copy example file to result folder
os.system(f"cp -r {root_path}/example {workflow_path}")

# copy log file to result folder
os.system(f"mkdir -p {workflow_path}/log/")
os.system(f"mv {root_path}/log/*.log {workflow_path}/log/")
