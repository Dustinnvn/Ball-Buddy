#!/usr/bin/env python3
import serial
import time
#import RPi.GPIO as GPIO
import os
from http.server import BaseHTTPRequestHandler, HTTPServer

host_name = '192.168.86.33'  # IP Address of Raspberry Pi
host_port = 8000


def getTemperature():
    temp = os.popen("/opt/vc/bin/vcgencmd measure_temp").read()
    return temp


class MyServer(BaseHTTPRequestHandler):

    def do_HEAD(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def _redirect(self, path):
        self.send_response(303)
        self.send_header('Content-type', 'text/html')
        self.send_header('Location', path)
        self.end_headers()

    def do_GET(self):
        html = '''
           <html>
           <head>  
           <head>  
           <body
            style="width:960px; margin: 20px auto;">
           <h1>Welcome to my Pet Ball</h1>
           <p>Current CPU temperature is {}</p>
           <p>Click on a button to move the ball launcher</p>  
           <form action="/" method="POST">
               Move X Motor:
               <input type="submit" name="submit" value="Right">
               <input type="submit" name="submit" value="Left">
           </form>
           <form action="/" method="POST">
               Move Y Motor:
               <input type="submit" name="submit" value="Up">
               <input type="submit" name="submit" value="Down">
               <input type="submit" name="submit" value="Cycle">

           </form>
           <button onclick="getElementById('demo').innerHTML = Date()">What is the time?</button>
           <p id="demo"></p>
           </body>
           </html>
        '''
        temp = getTemperature()
        self.do_HEAD()
        self.wfile.write(html.format(temp[5:]).encode("utf-8"))

    def do_POST(self):

        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode("utf-8")
        post_data = post_data.split("=")[1]
        #the input is coded as the button names aka post data d-down, u-up, 1-right, 2-left, 3-spin
        if post_data == 'Up':
            ser.write('u'.encode())
            time.sleep(1)
           
        elif post_data == 'Down':
            ser.write('d'.encode())
            time.sleep(1)
        elif post_data == 'Right':
            ser.write('1'.encode())
            time.sleep(1)
        elif post_data == 'Left':
            ser.write('2'.encode())
            time.sleep(1)
        elif post_data == 'Cycle':
            ser.write('4'.encode())
            time.sleep(1) 

        print("MODE is {}".format(post_data))
        self._redirect('/')  # Redirect back to the root url


# # # # # Main # # # # #

if __name__ == '__main__':
    
    ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1) #change ACM number as found from ls /dev/tty/ACM*
    ser.flush()
    http_server = HTTPServer((host_name, host_port), MyServer)
    print("Server Starts - %s:%s" % (host_name, host_port))
    
    try:
        http_server.serve_forever()
    except KeyboardInterrupt:
        http_server.server_close()