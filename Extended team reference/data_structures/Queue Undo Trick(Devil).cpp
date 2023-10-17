/**
 * Queue Undo Trick:
 * Given a data structure supporting some updates and last update undo(stack-like undo) this DS
 * solves the problem for undoing the first active(queue-like) update on the base data structure. 
 * 
 */

template<class DS, typename T>
struct queue_like_undo
{
	DS d;
	vector<pair<bool, T>> stk;
 
	void push_back(T x)
	{
		stk.push_back({ true, x });
		d.add(x.F, x.S);
	}
 
	void pop_front()
	{
		auto i = stk.end();
		for (int c = 0; ;) { c += (--i)->F ? -1 : +1; d.undo(); if (c >= 0 || i == stk.begin()) break; }
		auto j = stable_partition(i, stk.end(), [](auto &x){ return x.F; });
		if (i == stk.begin()) reverse(i, j), for_each(i, j, [](auto &x){ x.F = false; });
		for_each(i, prev(stk.end()), [&](auto &x){ d.add(x.S.F, x.S.S); });
		stk.pop_back();
	}
};