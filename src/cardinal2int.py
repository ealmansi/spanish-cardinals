#!/usr/bin/env python
# -*- coding: utf-8 -*-


import re;


class Tokenizer:
  def __init__(self, inp):
    self.tokens = inp.lower().encode('utf8')
    self.substitutions = [
      ("á", "a"), ("é", "e"), ("í", "i"), ("ó", "o"), ("ú", "u"), ("[^\w]", " "),
      ("(^| )un( |$)", " uno "), ("(^| )veintiun( |$)", " veintiuno "), ("(^| )cien( |$)", " ciento "), ("(^| )millon( |$)", " millones "), ("(^| )y( |$)", " "),
      ("(^| )once( |$)", " diez uno "), ("(^| )doce( |$)", " diez dos "), ("(^| )trece( |$)", " diez tres "), ("(^| )catorce( |$)", " diez cuatro "),
      ("(^| )quince( |$)", " diez cinco "), ("(^| )dieciseis( |$)", " diez seis "), ("(^| )diecisiete( |$)", " diez siete "), ("(^| )dieciocho( |$)", " diez ocho "), ("(^| )diecinueve( |$)", " diez nueve "),
      ("(^| )veintiuno( |$)", " veinte uno "), ("(^| )veintidos( |$)", " veinte dos "), ("(^| )veintitres( |$)", " veinte tres "), ("(^| )veinticuatro( |$)", " veinte cuatro "),
      ("(^| )veinticinco( |$)", " veinte cinco "), ("(^| )veintiseis( |$)", " veinte seis "), ("(^| )veintisiete( |$)", " veinte siete "), ("(^| )veintiocho( |$)", " veinte ocho "), ("(^| )veintinueve( |$)", " veinte nueve "),
    ]
    for (pattern, replace) in self.substitutions:
      self.tokens = re.sub(pattern, replace, self.tokens)
    self.tokens = filter(lambda x: len(x) > 0, self.tokens.split(" "))
    self.index = 0

  def empty(self):
    return self.index == len(self.tokens)

  def peek(self):
    if not self.empty():
      return self.tokens[self.index]
    else:
      return "$"

  def advance(self):
    if not self.empty():
      self.index = self.index + 1


def smallcardinal2int(tks):
  units = dict(zip(["cero", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"], range(0, 10)))
  tens = dict(zip(["diez", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"], range(10, 100, 10)))
  hundreds = dict(zip(["ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"], range(100, 1000, 100)))
  value = 0
  match = False
  if tks.peek() in hundreds:
    value = value + hundreds[tks.peek()]
    match = True
    tks.advance()
  if tks.peek() in tens:
    value = value + tens[tks.peek()]
    match = True
    tks.advance()
  if tks.peek() in units:
    value = value + units[tks.peek()]
    match = True
    tks.advance()
  if match:
    return value
  else:
    return None


def cardinal2int(tks):
  accum = 0
  m_0 = smallcardinal2int(tks)
  if tks.peek() == "$":
     return m_0
  if tks.peek() == "mil":
    tks.advance()
    m_1 = smallcardinal2int(tks)
    if not m_0: m_0 = 1
    if not m_1: m_1 = 0
    m_0 = m_0 * 1000 + m_1
    if tks.peek() == "$":
      return m_0
  if tks.peek() == "millones":
    tks.advance()
    m_0 = m_0 * 1000000
    if tks.peek() == "$":
      return m_0
    m_1 = smallcardinal2int(tks)
    if tks.peek() == "$":
      return m_0 + m_1
    if tks.peek() == "mil":
      tks.advance()
      m_2 = smallcardinal2int(tks)
      if not m_1: m_1 = 1
      if not m_2: m_2 = 0
      if tks.peek() == "$":
        return m_0 + m_1 * 1000 + m_2

  
def main():
  inp = u"cero"
  print cardinal2int(Tokenizer(inp))
  inp = u"doscientos treinta y nueve"
  print cardinal2int(Tokenizer(inp))
  inp = u"veintiun mil doscientos treinta y nueve"
  print cardinal2int(Tokenizer(inp))
  inp = u"veintiun mil"
  print cardinal2int(Tokenizer(inp))
  inp = u"siete millones veintiun mil doscientos treinta y nueve"
  print cardinal2int(Tokenizer(inp))
  inp = u"siete millones mil doscientos treinta y nueve"
  print cardinal2int(Tokenizer(inp))
  inp = u"siete millones mil"
  print cardinal2int(Tokenizer(inp))
  inp = u"mil uno millones y mil"
  print cardinal2int(Tokenizer(inp))
  inp = u"novecientos mil siete millones veintiun mil doscientos treinta y nueve"
  print cardinal2int(Tokenizer(inp))
  inp = u"novecientos noventa y nueve mil novecientos noventa y nueve millones novecientos noventa y nueve mil novecientos noventa y nueve"
  print cardinal2int(Tokenizer(inp))
  inp = u"Un Millón trescientos ochenta y Siete Mil Ochocientos VEINTITRÉS"
  print cardinal2int(Tokenizer(inp))


if __name__ == '__main__':
  main()