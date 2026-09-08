# Last updated: 2026. 9. 8. 오후 5:14:09
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    
    def leafSimilar(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        leaf1 = []
        leaf2 = []
        def getLeaf(root,result):
            if root.left is None and root.right is None: ## leafNode
                result.append(root.val)
            if root.left:
                getLeaf(root.left,result)
            if root.right:
                getLeaf(root.right,result)
            return
        getLeaf(root1,leaf1)
        getLeaf(root2,leaf2)
        print(leaf1,leaf2)
        return leaf1==leaf2
        
        