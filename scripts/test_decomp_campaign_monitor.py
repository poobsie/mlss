import unittest
from decomp_campaign_monitor import estimate


class EstimateTests(unittest.TestCase):
    def state(self):
        return {'identity': {'stages': [30, 300, 1800]}, 'draft_variants': 100,
                'runs': {}, 'matches': [], 'status': 'running'}

    def result(self, better=False):
        return {'artifacts': '/nonexistent', 'status': 'mismatch',
                'process': {'wall_seconds': 30}, 'best_source': 'best.c',
                'search': {'baseScore': 10, 'bestScore': 5 if better else 10}}

    def test_partial_pair_is_not_completed(self):
        state = self.state()
        state['runs']['f:hash:transmuter:0'] = self.result()
        self.assertEqual(estimate(state)['completed_drafts'], 0)
        state['runs']['f:hash:permuter:0'] = self.result()
        self.assertEqual(estimate(state)['completed_drafts'], 1)

    def test_improving_pair_requires_extension(self):
        state = self.state()
        state['runs'] = {'f:hash:transmuter:0': self.result(True),
                         'f:hash:permuter:0': self.result()}
        result = estimate(state)
        self.assertEqual(result['completed_drafts'], 0)
        self.assertEqual(result['stage_extensions'][0], 1)
        state['runs']['f:hash:transmuter:1'] = self.result()
        self.assertEqual(estimate(state)['completed_drafts'], 1)

    def test_exhaustion_has_zero_eta_including_skipped_drafts(self):
        state = self.state()
        state['status'] = 'draft_queue_exhausted'
        result = estimate(state)
        self.assertEqual(result['remaining_seconds'], 0)
        self.assertEqual(result['completed_drafts'], 100)

    def test_initial_range_is_ordered(self):
        result = estimate(self.state())
        self.assertLess(result['range_low_seconds'], result['remaining_seconds'])
        self.assertLess(result['remaining_seconds'], result['range_high_seconds'])


if __name__ == '__main__':
    unittest.main()
