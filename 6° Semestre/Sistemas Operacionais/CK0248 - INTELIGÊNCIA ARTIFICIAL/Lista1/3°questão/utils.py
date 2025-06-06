from queue import PriorityQueue

map_romania = {
    "Arad": [("Zerind", 75), ("Timisoara", 118), ("Sibiu", 140)],
    "Zerind": [("Arad", 75), ("Oradea", 71)],
    "Oradea": [("Zerind", 71), ("Sibiu", 151)],
    "Timisoara": [("Arad", 118), ("Lugoj", 111)],
    "Lugoj": [("Timisoara", 111), ("Mehadia", 70)],
    "Mehadia": [("Lugoj", 70), ("Drobeta", 75)],
    "Drobeta": [("Mehadia", 75), ("Craiova", 120)],
    "Craiova": [("Drobeta", 120), ("Rimnicu Vilcea", 146), ("Pitesti", 138)],
    "Sibiu": [("Arad", 140), ("Oradea", 151), ("Fagaras", 99), ("Rimnicu Vilcea", 80)],
    "Fagaras": [("Sibiu", 99), ("Bucareste", 211)],
    "Rimnicu Vilcea": [("Sibiu", 80), ("Craiova", 146), ("Pitesti", 97)],
    "Pitesti": [("Rimnicu Vilcea", 97), ("Craiova", 138), ("Bucareste", 101)],
    "Bucareste": [("Fagaras", 211), ("Pitesti", 101), ("Giurgiu", 90), ("Urziceni", 85)],
    "Giurgiu": [("Bucareste", 90)],
    "Urziceni": [("Bucareste", 85), ("Hirsova", 98), ("Vaslui", 142)],
    "Hirsova": [("Urziceni", 98), ("Eforie", 86)],
    "Eforie": [("Hirsova", 86)],
    "Vaslui": [("Urziceni", 142), ("Iasi", 92)],
    "Iasi": [("Vaslui", 92), ("Neamt", 87)],
    "Neamt": [("Iasi", 87)]
}

heuristics_bucharest = {
    "Arad": 366, "Bucareste": 0, "Craiova": 160, "Drobeta": 242, "Eforie": 161,
    "Fagaras": 178, "Giurgiu": 77, "Hirsova": 151, "Iasi": 226, "Lugoj": 244,
    "Mehadia": 241, "Neamt": 234, "Oradea": 380, "Pitesti": 98, "Rimnicu Vilcea": 193,
    "Sibiu": 253, "Timisoara": 329, "Urziceni": 80, "Vaslui": 199, "Zerind": 374
}

def greedy_search(start, goal):
    priority_queue = PriorityQueue()
    priority_queue.put((heuristics_bucharest[start], start))
    visited = set()
    path = []

    while not priority_queue.empty():
        _, city = priority_queue.get()
        path.append(city)

        if city == goal:
            return path

        visited.add(city)

        for neighbor, _ in map_romania[city]:
            if neighbor not in visited:
                priority_queue.put((heuristics_bucharest[neighbor], neighbor))

    return None

def a_star_search(start, goal):
    priority_queue = PriorityQueue()
    priority_queue.put((heuristics_bucharest[start], 0, start))
    visited = set()
    predecessors = {start: None}
    accumulated_cost = {start: 0}

    while not priority_queue.empty():
        _, current_cost, city = priority_queue.get()

        if city == goal:
            path = []
            while city:
                path.append(city)
                city = predecessors[city]
            return path[::-1]

        if city in visited:
            continue

        visited.add(city)

        for neighbor, cost in map_romania[city]:
            new_cost = current_cost + cost
            if neighbor not in accumulated_cost or new_cost < accumulated_cost[neighbor]:
                accumulated_cost[neighbor] = new_cost
                priority = new_cost + heuristics_bucharest[neighbor]
                priority_queue.put((priority, new_cost, neighbor))
                predecessors[neighbor] = city

    return None
