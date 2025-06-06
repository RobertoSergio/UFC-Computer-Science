class Objects:
    def __init__(self, parent_id, id):
        self.id = id
        self.root = self
        self.parent_id = parent_id
        self.children_tree = []
    
    def new_object(self, parent_id, object_id):
        object = Objects(parent_id, object_id)
        object.root = self
        parent = self.search_parent(parent_id)
        parent.children_tree.append(object)
        # print(f'{object_id} criado com sucesso')

    def search_parent(self, parent_id):
        if self.id == parent_id:
            return self
        for children in self.children_tree:
            id = children.search_parent(parent_id)
            if id:
                return id

    def all_children(self):
        all_children = []
        for children in self.children_tree:
            all_children.append(children.id)
            print(children.id)
            all_children = all_children + children.all_children()
        return all_children
    
    def all_parents(self):
        all_parents = []
        if self.parent_id is not None:
            parent = self.root.search_parent(self.parent_id)
            all_parents += parent.all_parents()  # Chama recursivamente os pais
            all_parents.append(self.parent_id)  # Adiciona o ID do pai atual
        return all_parents

