from typing import *
class Solution:
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        ans = sum([min(tickets[i], tickets[k]) for i in range(k)])
        ans += sum([min(tickets[i], tickets[k]-1) for i in range(k+1, len(tickets))])
        return ans