#!/usr/bin/env python3

import ntpath
import re
import wx

#print(wx.version())

class MyFrame(wx.Frame):
  filename = ''
  movex = 0.0
  movey = 0.0
  def __init__(self, parent, title):
    wx.Frame.__init__(self, parent, title=title, size=(320, 320))
    panel = wx.Panel(self)
    sizer = wx.BoxSizer(wx.VERTICAL)
    openFileDialog = wx.FileDialog(self, "Open", "", "", "Static templates (*.stm)|*.stm", wx.FD_OPEN | wx.FD_FILE_MUST_EXIST)
    openFileDialog.ShowModal()
    self.filename = openFileDialog.GetPath()
    openFileDialog.Destroy()
    labelfile = wx.StaticText(panel, label=ntpath.basename(self.filename))
    sizer.Add(labelfile, 0, wx.ALL | wx.EXPAND, 5)
    labelx = wx.StaticText(panel, label="Move X:")
    sizer.Add(labelx, 0, wx.ALL | wx.EXPAND, 5)
    self.textctrlx = wx.TextCtrl(panel, value='0.0')
    sizer.Add(self.textctrlx, 0, wx.ALL | wx.EXPAND, 5)
    labely = wx.StaticText(panel, label="Move Y:")
    sizer.Add(labely, 0, wx.ALL | wx.EXPAND, 5)
    self.textctrly = wx.TextCtrl(panel, value='0.0')
    sizer.Add(self.textctrly, 0, wx.ALL | wx.EXPAND, 5)
    button = wx.Button(panel, label="Move")
    button.Bind(wx.EVT_BUTTON, self.on_press)
    sizer.Add(button, 0, wx.ALL | wx.CENTER, 5)
    panel.SetSizer(sizer)
    self.Show()

  def on_press(self, event):
    print(ntpath.dirname(self.filename))
    print(self.filename)
    self.movex = float(self.textctrlx.GetValue())
    print(self.movex)
    self.movey = float(self.textctrly.GetValue())
    print(self.movey)
    f = open(self.filename, encoding="utf8")
    newcontent = ''
    line = f.readline()
    while line:
      result = re.match('.*\["([xy])"\] = ([-+]{0,1}[0-9\.]+),', line)
      if result:
        pos = float(result.group(2))
        newpos = pos
        if self.movex != 0.0 and result.group(1) == 'x':
          newpos = pos + self.movex
        if self.movey != 0.0 and result.group(1) == 'y':
          newpos = pos + self.movey
        newline = re.sub('[-+]{0,1}[0-9\.]+', str(newpos), line)
        newcontent += newline
      else:
        newcontent += line
      line = f.readline()
    f.close()
    print(newcontent)
    saveFileDialog = wx.FileDialog(self, "Save", "", "", "Static templates (*.stm)|*.stm", wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT)
    if saveFileDialog.ShowModal() != wx.ID_CANCEL:
      newfilename = saveFileDialog.GetPath()
      try:
        with open(newfilename, 'w', encoding="utf8") as f:
          f.write(newcontent)
          f.close()
      except IOError:
        print("IOError")
    saveFileDialog.Destroy()

app = wx.App()
frame = MyFrame(None, 'MoveIt')
app.MainLoop()
