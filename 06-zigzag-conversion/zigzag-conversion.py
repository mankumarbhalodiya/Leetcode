class Solution(object):
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        if numRows == 1 or numRows >= len(s):
            return s

        rows = [""] * numRows
        currentRow = 0
        goingDown = False

        for char in s:
            rows[currentRow] += char

            if currentRow == 0 or currentRow == numRows - 1:
                goingDown = not goingDown

            if goingDown:
                currentRow += 1
            else:
                currentRow -= 1

        return "".join(rows)