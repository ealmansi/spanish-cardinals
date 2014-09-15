#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def sign(n):
  return (n > 0) - (n < 0)


def int2cardinal(n_int):
  n, sg = abs(n_int), sign(n_int)
  if 999999999999 < n: return None
  t_0 = n % 1000; c_0 = smallint2cardinal(t_0); n = n // 1000
  t_1 = n % 1000; c_1 = smallint2cardinal(t_1); n = n // 1000
  t_2 = n % 1000; c_2 = smallint2cardinal(t_2); n = n // 1000
  t_3 = n % 1000; c_3 = smallint2cardinal(t_3); n = n // 1000
  n_car = '{c_3} mil, {c_2} millones, {c_1} mil, {c_0}'.format(c_3=c_3,
    c_2=c_2, c_1=c_1, c_0=c_0)
  n_car = handle_special_cases(n_car, sg)
  return n_car


def smallint2cardinal(n):
  hs = ['0hs', 'ciento', 'doscientos', 'trescientos', 'cuatrocientos',
    'quinientos', 'seiscientos', 'setecientos', 'ochocientos', 'novecientos']
  ts = ['0ts', 'diez', 'veinte', 'treinta', 'cuarenta', 'cincuenta',
    'sesenta', 'setenta', 'ochenta', 'noventa']
  us = ['0us', 'uno', 'dos', 'tres', 'cuatro', 'cinco', 'seis', 'siete',
    'ocho', 'nueve']
  u_0 = n % 10; c_0 = us[u_0]; n = n // 10
  u_1 = n % 10; c_1 = ts[u_1]; n = n // 10
  u_2 = n % 10; c_2 = hs[u_2]; n = n // 10
  n_car = '{c_2} {c_1} y {c_0}'.format(c_2=c_2, c_1=c_1, c_0=c_0)
  return n_car


def handle_special_cases(n_car, sg):
  substitutions = [
    ('0hs 0ts y 0us', 'cero'),
    ('ciento 0ts y 0us', 'cien 0ts y 0us'),
    (' 0ts y 0us', ''),
    (' y 0us', ''),
    ('0hs 0ts y uno mil,', 'mil,'),
    ('0hs 0ts y uno millones,', 'un millón,'),
    ('0hs ', ''),
    ('0ts y ', ''),
    ('cero mil, ', ''),
    ('mil, cero millones, ', 'mil millones, '),
    ('cero millones, ', ''),
    (', cero', ''),
    ('diez y uno', 'once'),
    ('diez y dos', 'doce'),
    ('diez y tres', 'trece'),
    ('diez y cuatro', 'catorce'),
    ('diez y cinco', 'quince'),
    ('diez y seis', 'dieciséis'),
    ('diez y siete', 'diecisiete'),
    ('diez y ocho', 'dieciocho'),
    ('diez y nueve', 'diecinueve'),
    ('veinte y uno', 'veintiuno'),
    ('veinte y dos', 'veintidos'),
    ('veinte y tres', 'veintitrés'),
    ('veinte y cuatro', 'veinticuatro'),
    ('veinte y cinco', 'veinticinco'),
    ('veinte y seis', 'veintiséis'),
    ('veinte y siete', 'veintisiete'),
    ('veinte y ocho', 'veintiocho'),
    ('veinte y nueve', 'veintinueve'),
    ('veintiuno mil,', 'veintiún mil,'),
    ('veintiuno millones,', 'veintiún millones,'),
    ('uno mil,', 'un mil,'),
    ('uno millones,', 'un millones,')
  ]
  n_car = ' ' + n_car + ' '
  for old, new in substitutions:
    n_car = n_car.replace(old, new)
  n_car = n_car.strip()
  if sg == -1: n_car = 'menos ' + n_car
  return n_car


def test():
  for n in range(-999999999999, 999999999999, 999999997):
    print(int2cardinal(n))


if __name__ == '__main__':
  test()
