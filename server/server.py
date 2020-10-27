#!/usr/bin/python3

import os
from datetime import datetime
try:
    import http.server as server
except ImportError:
    # Handle Python 2.x
    import SimpleHTTPServer as server


## TODO: Make a auth page to prevent others

class HTTPRequestHandler(server.SimpleHTTPRequestHandler):
    """Extend SimpleHTTPRequestHandler to handle PUT requests"""
    def do_PUT(self):
        """Save a file following a HTTP PUT request"""

        dateTime = datetime.now()
        filename = os.path.basename(self.path) + "_" + str(dateTime.hour)  + "." + str(dateTime.minute) + "." + str(dateTime.second)

        clientip = self.client_address[0]
        path = "storefile/" + clientip
        if not os.path.exists(path):
            os.makedirs(path)

        file_length = int(self.headers['Content-Length'])
        with open(path + "/" + filename, 'wb') as output_file:
            output_file.write(self.rfile.read(file_length))
        self.send_response(201, 'Created')
        self.end_headers()
        reply_body = 'Saved "%s"\n' % filename
        self.wfile.write(reply_body.encode('utf-8'))

if __name__ == '__main__':
    server.test(HandlerClass=HTTPRequestHandler)