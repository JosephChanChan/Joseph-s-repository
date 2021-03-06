
/**
 * Question Description:
 *  Write a function:
 * class Solution { public int solution(int[] A); }
 * that, given an array A of N integers, returns the smallest positive integer (greater than 0)
 * that does not occur in A.
 * For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
 * Given A = [1, 2, 3], the function should return 4.
 * Given A = [−1, −3], the function should return 1.
 * Write an efficient algorithm for the following assumptions:
 * N is an integer within the range [1..100,000];
 * each element of array A is an integer within the range [−1,000,000..1,000,000].
 *
 * Time complexity is required and the task should be finished in O(n) or O(n * logn).
 *
 * Analysis:
 *  using a trick like bitmap algorithm.
 *  Time complexity: O(n)
 *  Space complexity: O(max(nums[i]))
 *
 * @author Joseph
 * @since 2020-01-08 21:26
 */
public class MissingPositiveSmallestNum {

    public static void main(String[] args) {
        int[] nums = {1,2,0};
        MissingPositiveSmallestNum smallestNum = new MissingPositiveSmallestNum();
        int solution = smallestNum.solution(nums);
        System.out.println(solution);
    }

    public int solution(int[] nums) {
        int max = 0;
        boolean positive = false;

        // index 1 ~ 1000000
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > 0) {
                if (max < nums[i]) {
                    max = nums[i];
                }
                positive = true;
            }
        }

        if (!positive) return 1;

        int[] valueArr = new int[max + 1];

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > 0) {
                valueArr[nums[i]] = nums[i];
            }
        }

        for (int i = 1; i < valueArr.length; i++) {
            if (valueArr[i] == 0) {
                return i;
            }
        }

        return max + 1;
    }


}
