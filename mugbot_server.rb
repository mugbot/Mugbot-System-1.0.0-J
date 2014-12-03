#! /usr/bin/ruby
# -*- coding: utf-8 -*-

#Mugbot Project Tokyo City University Koike Lab. 2014  
#Mugbot System ver. 1.0.0.

require 'em-websocket'
require 'serialport'

#シリアルポート設定
port =  "/dev/ttyACM0"
#/dev/ttyACM0はRaspberry Piから見たArduinoのポート
sp = SerialPort.new(port, 9600, 8, 1, SerialPort::NONE)

#WebSocket設定
EventMachine::WebSocket.start(:host => "0.0.0.0", :port => 51234) do |ws|

  ws.onmessage { |msg|
   if msg[0,2]=="@x"
     msg.slice!(0,2)
     puts msg
     sp.write  msg+"x"
     sleep 0.01

     #目の上下のアクション
     #最初の2文字が@xであればその2文字を取り除いてxの値をArduinoに送信


   elsif msg[0,2]=="@y"
     msg.slice!(0,2)
     puts msg
     sp.write  msg+"y"
     sleep 0.01

     #首の左右のアクション
     #最初の2文字が@yであればその2文字を取り除いてyの値をArduinoに送信


   elsif msg[0,2]=="@z"
     msg.slice!(0,2)
     puts msg
     sp.write  msg+"z"
     sleep 0.01

    #目の明るさ変調のアクション
    #最初の2文字が@zであればその2文字を取り除いてzの値をArduinoに送信


   elsif msg[0,1]=="@"
     sp.putc msg[1,1]
     sleep 0.01

     #最初の1文字が@であれば@を取り除いてアクションを指示するアルファベット1文字をArduinoに送信


   else
     sp.putc  "t"
     system(`jsay  #{msg}`)
     sp.putc  "n"  
     # tをArduinoに送って口の点滅開始、発話させ、nを送って点滅終了 
   end
  }

end
