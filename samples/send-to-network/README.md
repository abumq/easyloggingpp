# Send to Network

You can use this sample to send your log messages to network as requested by many users. We are not able to add it to the library as this will require some stuffs to choose what network library to use.

This sample uses `asio` in `boost_system`

## Run

Compile using `compile.sh` file but **make sure you have correct path to boost include and compiled library**

```
mkdir bin
sh compile.sh network-logger.sh
```

Run a server (we are using netcat on mac for test purposes) on a different terminal

```
nc -l 9090
```

Now run `./bin/network-logger`


## More

You may need `ELPP_NO_LOG_TO_FILE` and `ELPP_NO_DEFAULT_LOG_FILE` depending on your needs.

Please refer to [doc](https://github.com/muflihun/easyloggingpp#configuration-macros) for further details on macros
