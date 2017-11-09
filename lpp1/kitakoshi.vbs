Set ie = WScript.CreateObject("InternetExplorer.Application","ie_")
ie.Navigate("https://nittc.tokyo-ct.ac.jp/xythoswfs/webui/_xy-e4168359_7-t_C5zhSCja")
ie.Visible = True
While ie.ReadyState <> 4 
WScript.Sleep(1000)
Wend
Set password = ie.Document.getElementById("password")
password.Value = "+81-42-668-5061"
Set okButtonId = ie.Document.getElementById("okButtonId")
okButtonId.click()