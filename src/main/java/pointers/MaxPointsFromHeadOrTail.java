package pointers;

/**
 * lc 1423 medium
 *
 * Analysis:
 *  窗口类。跳出惯性思维，意识到只能从左右两端连续取k张，中间一定剩下取不到的。
 * 去计算中间连续取不到的n-k张，找到一个最小的连续n-k长度窗口，剩下的k张就是可取的最大窗口。
 * 需要二刷
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 *
 * @author Joseph
 * @since 2021-01-24 16:26
 */
public class MaxPointsFromHeadOrTail {

    public int maxScore(int[] cardPoints, int k) {
        return minimumWindow(cardPoints, k);
    }

    // 反向思路，找长度n-k的最小的连续窗口，总体时间O(2n) 2ms AC
    private int minimumWindow(int[] cardPoints, int k) {
        int n = cardPoints.length;

        int[] preS = new int[n];
        preS[0] = cardPoints[0];
        for (int i = 1; i < n; i++) {
            preS[i]=preS[i-1]+cardPoints[i];
        }

        if (n == k) return preS[n-1];
        if (k == 1) return Math.max(cardPoints[0], cardPoints[n-1]);

        int min = Integer.MAX_VALUE;
        int i = 0, j = n-k-1;
        for ( ; i <= k; i++, j++) {
            if (i == 0) {
                min = Math.min(min, preS[j]);
            }
            else {
                min = Math.min(preS[j] - preS[i-1], min);
            }
        }
        return preS[n-1]-min;
    }

    // 60min done 按题意分开取左和右的连续k张，总体O(3n) 4ms AC
    private int headOrTail(int[] cardPoints, int k) {
        int[] preS = new int[cardPoints.length];
        preS[0] = cardPoints[0];
        for (int i = 1; i < cardPoints.length; i++) {
            preS[i] = preS[i-1] + cardPoints[i];
        }

        int n = cardPoints.length-1;
        if (cardPoints.length == k) {
            return preS[n];
        }
        if (k == 1) {
            return Math.max(cardPoints[0], cardPoints[n]);
        }

        // 计算左边 O(n)时间
        int i = k-1, j = 0, max = 0;
        for ( ; i >= 0; i--) {
            int sum = 0;
            j = i-(k-1);
            j = j < 0 ? cardPoints.length + j : j;
            if (j == 0) {
                sum = preS[i];
            }
            else {
                sum = preS[i] + (preS[n] - preS[j-1]);
            }
            max = Math.max(max, sum);
        }
        // 计算右边 O(n)时间
        i = n - (k-1); j = 0;
        for ( ; i <= n; i++) {
            int sum = 0;
            j = i+(k-1);
            j = j > n ? j%cardPoints.length : j;
            if (j == n) {
                sum = preS[j] - preS[i-1];
            }
            else {
                sum = preS[n] - preS[i-1] + preS[j];
            }
            max = Math.max(max, sum);
        }
        return max;
    }
}
