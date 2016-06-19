M = [[ 0,  0,  0,  0,  0 ],
     [ 0,  1,  2,  3,  4 ],
     [ 0,  2, -1,  4, -3 ],
     [ 0,  3, -4, -1,  2 ],
     [ 0,  4,  3, -2, -1 ]]

def mul(a, b):
  sign = 1 if a * b > 0 else -1
  return sign * M[abs(a)][abs(b)]

def multiply_all(S, L, X):
  value = 1
  for i in range(X):
    for j in range(L):
      value = mul(value, S[j])
  return value

def construct_first_two(S, L, X):
  i_value = 1
  j_value = 1
  for i in range(X):
    for j in range(L):
      if i_value != 2:
        i_value = mul(i_value, S[j])
      elif j_value != 3:
        j_value = mul(j_value, S[j])
  return i_value == 2 and j_value == 3

for tc in range(input()):
  L, X = map(int, raw_input().split())
  # maps 'i' => 2, 'j' => 3, 'k' => 4
  S = [(ord(v) - ord('i') + 2) for v in raw_input()]
  ok1 = multiply_all(S, L, X) == -1
  ok2 = construct_first_two(S, L, X)
  print "Case #%d: %s" % (tc + 1,
    "YES" if ok1 and ok2 else "NO")