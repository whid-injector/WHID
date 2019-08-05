const char InputModePage[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<head><title>ESPloit Input Mode</title></head>
<body>
<a href="/esploit"><- BACK TO INDEX</a><br>
<b>InputMode</b><br>
Note: On configuaration page set "Delay Before Starting a Live Payload:" to "0" under "Payload Settings:" to avoid a delay when using Input Mode.
<br><br>
<table>
<tr>
<td>
<FORM action="/runlivepayload" method="post" id="print" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="print" rows="1" cols="100" name="livepayload">Print:</textarea>
</td>
</tr><tr>
<td>
<INPUT type="submit" form="print" value="Send Text"></form>
</td>
</tr>
</table>
<br>
<table style="text-align: center; display: inline-block;">
<tr>
<td>Mouse</td>
<td>
<FORM action="/runlivepayload" method="post" id="up" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="up" rows="1" cols="100" name="livepayload" hidden="1">MouseMoveUp:20</textarea>
<INPUT type="submit" form="up" value="Up"></form>
</td>
<td></td>
<td>
<FORM action="/runlivepayload" method="post" id="clickleft" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="clickleft" rows="1" cols="100" name="livepayload" hidden="1">MouseClickLEFT:</textarea>
<INPUT type="submit" form="clickleft" value="Left Click"></form>
</td>
</tr>
<tr>
<td>
<FORM action="/runlivepayload" method="post" id="left" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="left" rows="1" cols="100" name="livepayload" hidden="1">MouseMoveLeft:20</textarea>
<INPUT type="submit" form="left" value="Left"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="click" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="click" rows="1" cols="100" name="livepayload" hidden="1">MouseClickLEFT:</textarea>
<INPUT type="submit" form="click" value="Click"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="right" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="right" rows="1" cols="100" name="livepayload" hidden="1">MouseMoveRight:20</textarea>
<INPUT type="submit" form="right" value="Right"></form>
</td>
<td></td>
</tr>
<tr>
<td></td>
<td>
<FORM action="/runlivepayload" method="post" id="down" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="down" rows="1" cols="100" name="livepayload" hidden="1">MouseMoveDown:20</textarea>
<INPUT type="submit" form="down" value="Down"></form>
</td>
<td></td>
<td>
<FORM action="/runlivepayload" method="post" id="rightclick" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="rightclick" rows="1" cols="100" name="livepayload" hidden="1">MouseClickRIGHT:</textarea>
<INPUT type="submit" form="rightclick" value="Right Click"></form>
</td>
</tr>
</table>

<table style="text-align: center; display: inline-block;">
<tr>
<td>ArrowKeys</td>
<td>
<FORM action="/runlivepayload" method="post" id="a_up" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_up" rows="1" cols="100" name="livepayload" hidden="1">Press:218</textarea>
<INPUT type="submit" form="a_up" value="Up"></form>
</td>
<td>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="a_tab" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_tab" rows="1" cols="100" name="livepayload" hidden="1">Press:179</textarea>
<INPUT type="submit" form="a_tab" value="Tab"></form>
</td>
</tr>
<tr>
<td>
<FORM action="/runlivepayload" method="post" id="a_left" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_left" rows="1" cols="100" name="livepayload" hidden="1">Press:216</textarea>
<INPUT type="submit" form="a_left" value="Left"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="a_enter" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_enter" rows="1" cols="100" name="livepayload" hidden="1">Press:176</textarea>
<INPUT type="submit" form="a_enter" value="Enter"></form></td>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="a_right" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_right" rows="1" cols="100" name="livepayload" hidden="1">Press:215</textarea>
<INPUT type="submit" form="a_right" value="Right"></form>
</td>
<td><FORM action="/runlivepayload" method="post" id="a_alttab" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_alttab" rows="1" cols="100" name="livepayload" hidden="1">Press:130+179</textarea>
<INPUT type="submit" form="a_alttab" value="Alt+Tab"></form></td>
</tr>
<tr>
<td></td>
<td>
<FORM action="/runlivepayload" method="post" id="a_down" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_down" rows="1" cols="100" name="livepayload" hidden="1">Press:217</textarea>
<INPUT type="submit" form="a_down" value="Down"></form>
</td>
<td></td>
<td>
<FORM action="/runlivepayload" method="post" id="a_shifttab" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="a_shifttab" rows="1" cols="100" name="livepayload" hidden="1">Press:133+179</textarea>
<INPUT type="submit" form="a_shifttab" value="Shift+Tab"></form>
</td>
</tr>
</table>
<br>
<table>
<tr>
<td>
<FORM action="/runlivepayload" method="post" id="println" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="println" rows="1" cols="100" name="livepayload">PrintLine:</textarea>
</td>
</tr><tr>
<td><INPUT type="submit" form="println" value="Send Text+Enter"></form></td>
</tr>
</table>
<br>
<table>
<tr>
<td>Function Keys:</td>
<td>
<FORM action="/runlivepayload" method="post" id="f1" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f1" rows="1" cols="100" name="livepayload" hidden="1">Press:194</textarea>
<INPUT type="submit" form="f1" value="F1"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f2" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f2" rows="1" cols="100" name="livepayload" hidden="1">Press:195</textarea>
<INPUT type="submit" form="f2" value="F2"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f3" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f3" rows="1" cols="100" name="livepayload" hidden="1">Press:196</textarea>
<INPUT type="submit" form="f3" value="F3"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f4" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f4" rows="1" cols="100" name="livepayload" hidden="1">Press:197</textarea>
<INPUT type="submit" form="f4" value="F4"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f5" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f5" rows="1" cols="100" name="livepayload" hidden="1">Press:198</textarea>
<INPUT type="submit" form="f5" value="F5"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f6" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f6" rows="1" cols="100" name="livepayload" hidden="1">Press:199</textarea>
<INPUT type="submit" form="f6" value="F6"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f7" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f7" rows="1" cols="100" name="livepayload" hidden="1">Press:200</textarea>
<INPUT type="submit" form="f7" value="F7"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f8" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f8" rows="1" cols="100" name="livepayload" hidden="1">Press:201</textarea>
<INPUT type="submit" form="f8" value="F8"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f9" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f9" rows="1" cols="100" name="livepayload" hidden="1">Press:202</textarea>
<INPUT type="submit" form="f9" value="F9"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f10" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f10" rows="1" cols="100" name="livepayload" hidden="1">Press:203</textarea>
<INPUT type="submit" form="f10" value="F10"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f11" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f11" rows="1" cols="100" name="livepayload" hidden="1">Press:204</textarea>
<INPUT type="submit" form="f11" value="F11"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="f12" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="f12" rows="1" cols="100" name="livepayload" hidden="1">Press:205</textarea>
<INPUT type="submit" form="f12" value="F12"></form>
</td>
</tr>
</table>
<table>
<tr>
<td>Misc Keys:</td>
<td>
<FORM action="/runlivepayload" method="post" id="esc" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="esc" rows="1" cols="100" name="livepayload" hidden="1">Press:177</textarea>
<INPUT type="submit" form="esc" value="ESC"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="home" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="home" rows="1" cols="100" name="livepayload" hidden="1">Press:210</textarea>
<INPUT type="submit" form="home" value="HOME"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="end" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="end" rows="1" cols="100" name="livepayload" hidden="1">Press:213</textarea>
<INPUT type="submit" form="end" value="END"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="insert" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="insert" rows="1" cols="100" name="livepayload" hidden="1">Press:209</textarea>
<INPUT type="submit" form="insert" value="INSERT"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="del" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="del" rows="1" cols="100" name="livepayload" hidden="1">Press:212</textarea>
<INPUT type="submit" form="del" value="DEL"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="bs" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="bs" rows="1" cols="100" name="livepayload" hidden="1">Press:178</textarea>
<INPUT type="submit" form="bs" value="BACKSPACE"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="space" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="space" rows="1" cols="100" name="livepayload" hidden="1">Press:32</textarea>
<INPUT type="submit" form="space" value="SPACE BAR"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="pu" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="pu" rows="1" cols="100" name="livepayload" hidden="1">Press:211</textarea>
<INPUT type="submit" form="pu" value="PAGE UP"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="pd" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="pd" rows="1" cols="100" name="livepayload" hidden="1">Press:214</textarea>
<INPUT type="submit" form="pd" value="PAGE DOWN"></form>
</td>
</tr>
</table>
<table>
<tr>
<td>Win:</td>
<td>
<FORM action="/runlivepayload" method="post" id="wingui" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="wingui" rows="1" cols="100" name="livepayload" hidden="1">Press:131</textarea>
<INPUT type="submit" form="wingui" value="GUI-Key"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="runprompt" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="runprompt" rows="1" cols="100" name="livepayload" hidden="1">Press:131+114</textarea>
<INPUT type="submit" form="runprompt" value="GUI+r"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="cmd" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="cmd" rows="1" cols="100" name="livepayload" hidden="1">PrintLine:cmd</textarea>
<INPUT type="submit" form="cmd" value="cmd+EnterKey"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="osk" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="osk" rows="1" cols="100" name="livepayload" hidden="1">PrintLine:osk</textarea>
<INPUT type="submit" form="osk" value="osk+EnterKey"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="altf4" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="altf4" rows="1" cols="100" name="livepayload" hidden="1">Press:130+197</textarea>
<INPUT type="submit" form="altf4" value="Alt+F4"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="ctrlaltdel" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="ctrlaltdel" rows="1" cols="100" name="livepayload" hidden="1">Press:128+130+212</textarea>
<INPUT type="submit" form="ctrlaltdel" value="Ctrl+Alt+Del"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="ctrlshiftesc" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="ctrlshiftesc" rows="1" cols="100" name="livepayload" hidden="1">Press:128+129+177</textarea>
<INPUT type="submit" form="ctrlshiftesc" value="Ctrl+Shift+Esc"></form>
</td>
</tr>
</table>
<br>
<table>
<tr>
<td>Mac:</td>
<td>
<FORM action="/runlivepayload" method="post" id="z" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="z" rows="1" cols="100" name="livepayload" hidden="1">Press:122</textarea>
<INPUT type="submit" form="z" value="Right of Left Shift Key, z"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="fwdslash" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="fwdslash" rows="1" cols="100" name="livepayload" hidden="1">Press:47</textarea>
<INPUT type="submit" form="fwdslash" value="Left of Right Shift Key, /"></form>
</td>
</tr>
</table>
<br>
<table>
<tr>
<td>Linux:</td>
<td>
<FORM action="/runlivepayload" method="post" id="altf2" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="altf2" rows="1" cols="100" name="livepayload" hidden="1">Press:134+195</textarea>
<INPUT type="submit" form="altf2" value="Alt+F2, Application Finder"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="gterm" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="gterm" rows="1" cols="100" name="livepayload" hidden="1">PrintLine:gnome-terminal</textarea>
<INPUT type="submit" form="gterm" value="gnome-terminal+EnterKey"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="ctrlc" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="ctrlc" rows="1" cols="100" name="livepayload" hidden="1">Press:128+99</textarea>
<INPUT type="submit" form="ctrlc" value="CTRL+c"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="ctrlx" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="ctrlx" rows="1" cols="100" name="livepayload" hidden="1">Press:128+120</textarea>
<INPUT type="submit" form="ctrlx" value="CTRL+x"></form>
</td>
</tr>
</table>
<br>
<table>
<tr>
<td>Bios:</td>
<td>
<FORM action="/runlivepayload" method="post" id="bf1" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="bf1" rows="1" cols="100" name="livepayload" hidden="1">Press:194</textarea>
<INPUT type="submit" form="bf1" value="F1"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="bf2" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="bf2" rows="1" cols="100" name="livepayload" hidden="1">Press:195</textarea>
<INPUT type="submit" form="bf2" value="F2"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="bf8" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="bf8" rows="1" cols="100" name="livepayload" hidden="1">Press:201</textarea>
<INPUT type="submit" form="bf8" value="F8"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="bf12" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="bf12" rows="1" cols="100" name="livepayload" hidden="1">Press:205</textarea>
<INPUT type="submit" form="bf12" value="F12"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="bdel" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="bdel" rows="1" cols="100" name="livepayload" hidden="1">Press:212</textarea>
<INPUT type="submit" form="bdel" value="DEL"></form>
</td>
<td>
<FORM action="/runlivepayload" method="post" id="besc" target="iframe">
<INPUT type="radio" name="livepayloadpresent" value="1" hidden="1" checked="checked">
<textarea style ="width: 100%;" form="besc" rows="1" cols="100" name="livepayload" hidden="1">Press:177</textarea>
<INPUT type="submit" form="besc" value="ESC"></form>
</td>
</tr>
</table>
<br><hr><br><iframe style="visibility: hidden;" src="/runlivepayload" name="iframe"></iframe>

</body>
</html>
)=====";
