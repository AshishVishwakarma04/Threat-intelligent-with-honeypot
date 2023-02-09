import socket
import requests
from twilio.rest import Client

def start_honeypot():
    port = int(input("Enter port here : "))
    ip = "10.0.2.15"
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((ip, port)) # change the IP address and port as desired
    s.listen(5)
    print(f"[+]Honeypot running at IP address {ip} and port {port}")
    
    account_sid = '<twillio account sid>'
    auth_token = '<twillio account auth token>'
    twilio_client = Client(account_sid, auth_token)

    log_file = open("honeypot_logs.txt", "a") # open the log file in append mode

    while True:
        try:
            client, addr = s.accept()
            print("[+]Detected connection from IP address:", addr[0])
            client_request = client.recv(1024).decode() # receive the client's request
            if client_request.startswith("GET"): # check if the request is a GET request
                log_file.write("GET request received from IP address: " + addr[0] + "\n")
                log_file.write("Request: " + client_request + "\n")
                log_file.flush() # ensure that the log data is written to the file immediately
            message = twilio_client.messages.create( 
                                            from_='whatsapp:+14155238886',  
                                            body='Your device has be attacked',    
                                            to='whatsapp:+<your number here>' 
                                        ) 
            
            log_file.write("Detected connection from IP address: " + addr[0] + "\n")
            log_file.flush() # ensure that the log data is written to the file immediately
        except Exception:
            print("[+]Error Encountered")   
        finally:
            print("[+] Closing connection...")
            
            client.close()
    log_file.close()

start_honeypot()
