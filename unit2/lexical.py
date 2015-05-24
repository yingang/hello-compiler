import sys

# 判断是否合法的C变量名，如果用正则表达式应该是[_a-zA-Z][_a-zA-Z0-9]*
def valid_var_name(word):
  if not word[0].isalpha() and not word[0] == '_':
    return False

  for ch in word:
    if not ch.isalnum() and not ch == '_':
      return False

  return True

# 将输入文件的内容按空格或回车分隔为一个个的token，包含行列信息
def tokenize(filepath):
  token_list = []
  ln = 0

  for line in open(filepath):
    ln = ln + 1
    word = ""
    col = 0
    token_col = 0

    for ch in line:
      col += 1

      if ch == " " or ch == "\n":
        if word:
          token_list.append([word, ln, token_col])
          word = ""
      elif word:
        word += ch
      else:
        word += ch
        token_col = col

    if word:
      token_list.append([word, ln, token_col])

  return token_list

# 解析输出token列表中的内容
def parse_token(token):
  word, ln, col = token
 
  if word.isdigit():
    print "NUM(" + word + ")",
  elif word == "if":
    print "IF",
  elif valid_var_name(word):
    print "ID(" + word + ")",
  else:
    print "INVALID (" + word + ")",

  print "(" + str(ln) + ", " + str(col) + ")"

if __name__ == '__main__':
  script, filepath = sys.argv
  for token in tokenize(filepath):
    parse_token(token)