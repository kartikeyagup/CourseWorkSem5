# !/bin/bash
# script to start the server, which also starts the TA-AI client :P

echo "\033[95mextra options: sh startServer <port_no> <board_sz> <max_clients> \033[0m"
port=$1
if [ -z "$1" ];	then
	port=$(grep port: server/config.txt | sed 's/port: //g')
fi

# this seemd weird, but is not :p
cd client
python client.py $port localhost TA-AI '../server/ta_run.sh' 0.2 &

cd ../server
python server.py $port $2 $3
