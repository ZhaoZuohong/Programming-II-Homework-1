/*
 * 程序设计II 第一次作业
 * PB17000005 赵作竑
 * 2020年3月12日
 * http://bailian.openjudge.cn/practice/2808/
 * 
 * 主要思路：先将各个区域按照开始位置从小到大排序，
 * 之后依次处理各个区域。
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 砍树的区域
typedef struct
{
    int begin; // 区域的开始
    int end; // 区域的结束
} Area;

// 用区域的开始对区域进行比较，一会优先队列要用到
struct AreaCmp {
    bool operator()(Area a, Area b)
    {
        return a.begin > b.begin;
    }
};

// 砍树区域的优先队列
priority_queue<Area, vector<Area>, AreaCmp> pqAreas;

int main()
{
    int iTreesNum;
    int iInputLines;

    cin >> iTreesNum >> iInputLines;

    // 树的个数等于马路长度+1;
    ++iTreesNum;

    // 读取区域的数据
    for (int i = 0; i < iInputLines; ++i) {
        int a, b;
        cin >> a >> b;
        Area tmp;

        // 这里是在考虑区域的终点可能大于起点，要把它们换过来
        tmp.begin = min(a, b);
        tmp.end = max(a, b);
        pqAreas.push(tmp);
    }

    // 循环开始前的准备
    // iCuttingPosition是标记以前处理过的区域的最右边的位置，
    // 在iCuttingPosition及左边的位置的树都被砍过了。
    int iCuttingPosition = pqAreas.top().end;
    // 计算在砍过第一个区域之后剩下多少树
    iTreesNum -= pqAreas.top().end - pqAreas.top().begin + 1;
    pqAreas.pop();

    // 处理第i个区域
    for (int i = 0; i < iInputLines - 1; ++i) {
        // 如果下一个区域的结束位置小于等于iCuttingPosition：
        // 0                      iCuttingPosition
        // +----------------------+
        //        +-----------+
        // 这个时候跳过这个区域。
        if (pqAreas.top().end > iCuttingPosition) {
            // 如果下一个区域的结束位置大于iCuttingPosition：
            // 分为两种情况：
            // 第一种：开始位置小于等于iCuttingPosition：
            // 0                      iCuttingPosition
            // +----------------------+
            //        +--------------------+
            // 这时从iCuttingPosition开始向后计算；
            // 第二种：开始位置大于iCuttingPosition：
            // 0                      iCuttingPosition
            // +----------------------+
            //                            +-----------+
            // 这时计算整个新的区域。
            if (pqAreas.top().begin <= iCuttingPosition) {
                iTreesNum -= pqAreas.top().end - iCuttingPosition;
            } else {
                iTreesNum -= pqAreas.top().end - pqAreas.top().begin + 1;
            }
            // 最后更新iCuttingPosition。
            iCuttingPosition = pqAreas.top().end;
        }
        pqAreas.pop();
    }

    cout << iTreesNum << endl;

    return 0;
}