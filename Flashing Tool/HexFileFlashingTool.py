############################################################
#  Authors : Youssef Khaled Ahmed (558)                    #
#            Mark Ehab Tawfik (201)                        #
#            Hazem Mohamed Ezzeldin (1297)                 #
#            Azza Saeed Mohammed Gad (912)                 #
#            MennaTullah Ahmed Farrag Hefny (116)          #
#                                                          #
#  Date    : Oct 1, 2023                                   #
#                                                          #
#  SWC     : Hex File Flashing Tool                        #
############################################################ 
#                        Description                       #
############################################################
# A tool used to send a hex file record by record through  #
# seiral port from PC (Server) to Gateway ECU              #
############################################################


# Libraries Included
import serial

# The serial port of the ttl module
port = "COM6"

# The baud rate of the ttl module
baudRate = 9600  

# Open the serial port
ser = serial.Serial(port, baudRate)

"""
Opens a .hex file as a .txt file.

Args:
  hex_file_path: The path to the .hex file.
  text_file_path: The path to the .txt file.
  encoding: The encoding of the .txt file.
"""
def hex_to_text(hex_file_path):
  with open(hex_file_path, "r") as hex_file:
    ACK = ""
    for line in hex_file:
        for i in range(len(line)):
            ser.write((chr(ord(line[i][0]))).encode())
            print(line[i][0], end="")
        ACK = ser.read(2).decode('ascii')
        print("ACK", ACK)

    ser.close()

# Program Entry Point
if __name__ == "__main__":
      
  # Path of hex file of the app to flashed in bank 1 <0x08008000> 
  hexFilePath = r"E:\EUI\Projects\firmware-over-CAN\Application_1\Debug\Application_1.hex"

  # Path of hex file of the app to flashed in bank 2 <0x08010000>
  # hexFilePath = r"E:\EUI\Projects\firmware-over-CAN\Application_2\Debug\Application_2.hex"

  """
  Parse hex file to text file then traverse over each 
  record in that file and send it individually through 
  serial port to Gateway ECU then wait untill Gateway ECU
  sends you back an acknowledge to send the next record
  untill the file is sent completely
  """
  hex_to_text(hexFilePath)