"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	$('#functionTest').click(function(){
		sendMonitorCommand("test");
	});

	$('#functionRecord').click(function(){
		sendMonitorCommand("record");
	});

	socket.on('commandTest', function(result) {
		$('#status-text').text(result);
	});

	socket.on('commandRecord', function(result) {
		$("#functionRecord").prop("value", "Recording...");
		$("#functionRecord").attr('disabled','disabled');

		setTimeout(function() {
		$("#functionRecord").removeAttr('disabled');
        }, 45000);
	});
});

function sendMonitorCommand(message) {
	socket.emit('monitor', message);
};