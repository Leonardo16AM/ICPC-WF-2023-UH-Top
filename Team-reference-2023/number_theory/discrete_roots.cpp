vector<ll> discrete_root(ll k, ll a, ll n){
	if (a == 0) return {0};
	ll g = primitive_root(n);
	ll sq = (ll) sqrt(n + .0) + 1;
	vector<pair<ll, ll>> dec(sq);
	for (ll i = 1; i <= sq; ++i)
		dec[i - 1] = {pow(g, ll(i * sq * 1ll * k % (n - 1)), n), i};
	sort(dec.begin(), dec.end());
	ll any_ans = -1;
	for (int i = 0; i < sq; ++i){
		ll my = ll(pow(g, ll(i * 1ll * k % (n - 1)), n) * 1ll * a % n);
		auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0ll));
		if (it != dec.end() && it->first == my){
			any_ans = it->second * sq - i;
			break;
		}
	}
	if (any_ans == -1) return {};
	ll delta = (n - 1) / __gcd(k, n - 1);
	vector<ll> ans;
	for (ll cur = any_ans % delta; cur < n - 1; cur += delta)
		ans.push_back(pow(g, cur, n));
	sort(ans.begin(), ans.end());
	return ans;
}
