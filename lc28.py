class Solution:
    def strStr(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)
        # kmp[i] 是长为 i 的 t 的子串的最长真前缀与真后缀相等的长度，无解为 0
        kmp = [0] * (nt + 1)
        j = 0
        for i in range(2,nt+1):
            while j>0 and t[j]!=t[i-1]:
                j = kmp[j]
            if t[j]==t[i-1]:
                j+=1
            kmp[i] = j
        print(kmp)
        j = 0
        for i in range(ns):
            while j>0 and s[i]!=t[j]:
                j = kmp[j]
            if s[i]==t[j]:
                j+=1
            if j==nt:
                return i-nt+1
        return -1
    
s = Solution()
print(s.strStr("bcdfsfesrsdfersdf","aaaa"))
print(s.strStr("bcdfsfesrsdfersdf","abcbc"))
print(s.strStr("abacabadabacabaceabacabadabacabacabacabadabacabaceabacabadabacabac","abacabadabacabaeabacabadabacabac"))