var express = require('express');
var net = require('net');
var app = express();
var beacons = {};

var server = net.createServer(function(stream) {
	stream.on('data', function(c) {
		//console.log('data:', c.toString());
		var beacs = c.toString().split(',');
		beacs[5] = beacs.replace(/ /g,'-');
		beacons[beacs[0] + "_" +  beacs[5]] = beacs;
	});
	stream.on('end', function() {
		startListening();
		//server.close();
	});
});

app.get('/',function(req,res) {
	res.sendfile('index.html');
});

app.get('/v1/beacons',function(req,res) {
	res.setHeader('Content-Type','application/json');
	res.send(beacons);
});

function startListening() {
	server.listen('/tmp/ibeacon.sock');
}


var port = process.env.PORT || 5000;
app.listen(port,function() {
	startListening();
	console.log('Listening on ' + port);
});
