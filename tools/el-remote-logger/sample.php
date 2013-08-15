<?php

class RemoteConnection {

    private $server_host;
    private $server_port;
    private $sock;

    private static $instance; 

    private function __construct() {
        $this->server_host = "127.0.0.1";
        $this->server_port = 1590;
    }

    function __destruct() {
    }

    public static function getInstance() { 
        if(!self::$instance) { 
            self::$instance = new self(); 
        } 
        return self::$instance;
    } 

    public function connect() {
        $this->sock = socket_create(AF_INET, SOCK_STREAM, 0);
        socket_connect($this->sock, $this->server_host, $this->server_port) or die("Could not estabilish connection to server");
    }

    public function disconnect() {
        socket_close($this->sock);
    }

    public function read() {
        return socket_read($this->sock, 1024);
    }

    public function write($msg) {
        $this->connect();
        socket_write($this->sock, $msg, strlen($msg));
        $this->disconnect();
    }
}

class el {
    const Info = 0;
    const Debug = 1;
    const Warning = 2;
    const Error = 3;
    const Fatal = 4;
    const Trace = 5;
    const Verbose = 6;

    public static function write($msg, $level) {
        RemoteConnection::getInstance()->write(el::buildMsg($msg, $level));
    }

    private static function buildMsg($msg, $level) {
       $msgArr['level'] = (int)$level;
       $msgArr['log'] = $msg;
       $msgArr['user'] = "[usr]";
       $msgArr['host'] = "[host]";
       $msgArr['vlevel'] = (int)0;
       $msgArr['func'] = "[func]";
       $msgArr['loc'] = "[loc]";
       return json_encode($msgArr);
    }
}

  for ($i = 0; $i < 100; $i++)
    el::write("Flying high...", el::Info);
?>

