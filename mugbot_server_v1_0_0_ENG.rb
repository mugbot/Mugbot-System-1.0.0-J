#! / Usr / bin / ruby
# - * - Coding: utf-8 - * -
#Needs to be placed in /bin/ruby or uses /bin/ruby to execute?

#Mugbot Project Tokyo City University Koike Lab. 2014  
#Mugbot System ver. 1.0.0.
#English translation by Hans Chun using Google Translate

require 'em-websocket'
require 'serialport'

# Serial port settings
port = "/ dev / ttyACM0"
# / Dev / ttyACM0 of Arduino as seen from the Raspberry Pi port
sp = SerialPort.new (port, 9600, 8, 1, SerialPort :: NONE)

#WebSocket Settings
EventMachine :: WebSocket.start (: host => "0.0.0.0",: port => 51234) do | ws |

	ws.onmessage {| msg |
	if msg [0,2] == "@ x"
		msg.slice! (0,2)
		It puts msg
		sp.write msg + "x"
		sleep 0.01
	#May be wrong
    # Upper and lower action of the eyes ?? Reversed with y??

	elsif msg [0,2] == "@ y"
		msg.slice! (0,2)
		It puts msg
		sp.write msg + "y"
		sleep 0.01
	#May be wrong
    #Left and right of action of neck ?? Reversed with x??

	elsif msg [0,2] == "@ z"
		msg.slice! (0,2)
		It puts msg
		sp.write msg + "z"
		sleep 0.01
    # Modulate brightness of eyes

	elsif msg [0,1] == "@"
		sp.putc msg [1,1]
		sleep 0.01
    # Send a single character message?


   else
     sp.putc "t"
     system (`jsay # {msg}`)
     sp.putc "n"  
     #"t" signal makes mouth start flashing (talking). "n" signal stops.
   end
  }

end
