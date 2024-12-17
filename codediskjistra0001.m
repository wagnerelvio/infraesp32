function dijkstra_example()
    % Lista de nós da rede
    nodes = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    % Número de nós
    n = length(nodes);

    % Inicializar o grafo com Inf
    graph = inf(n, n);
    
    % Definir pesos para as conexões (bidirecionais)
    graph(1, 2) = 4;   graph(2, 1) = 4;   % A ↔ B
    graph(1, 3) = 2;   graph(3, 1) = 2;   % A ↔ C
    graph(1, 7) = 2;   graph(7, 1) = 2;   % A ↔ G
    graph(2, 4) = 4;   graph(4, 2) = 4;   % B ↔ D
    graph(3, 5) = 15;  graph(5, 3) = 15;  % C ↔ E
    graph(3, 7) = 4;   graph(7, 3) = 4;   % C ↔ G
    graph(4, 6) = 6;   graph(6, 4) = 6;   % D ↔ F
    graph(5, 6) = 12;  graph(6, 5) = 12;  % E ↔ F
    graph(7, 5) = 10;  graph(5, 7) = 10;  % G ↔ E
    graph(7, 6) = 5;   graph(6, 7) = 5;   % G ↔ F
    graph(7, 4) = 20;  graph(4, 7) = 20;  % G ↔ D

    % Origem e destino
    startNode = 'A'; % Nó inicial
    endNode = 'D';   % Nó final
    
    % Índices correspondentes
    startIdx = find(strcmp(nodes, startNode));
    endIdx = find(strcmp(nodes, endNode));

    % Chamar Dijkstra
    [distances, predecessors] = dijkstra(graph, startIdx);

    % Mostrar a distância mínima e o caminho
    fprintf('Distância entre %s e %s: %d\n', startNode, endNode, distances(endIdx));
    
    path = reconstruct_path(predecessors, startIdx, endIdx);
    fprintf('Caminho mais curto: ');
    for i = 1:length(path)
        fprintf('%s ', nodes{path(i)});
    end
    fprintf('\n');
end

% Algoritmo de Dijkstra
function [dist, pred] = dijkstra(graph, source)
    n = size(graph, 1);
    dist = inf(1, n);
    visited = false(1, n);
    pred = NaN(1, n);
    dist(source) = 0; % Distância da origem é 0
    
    for i = 1:n
        % Seleciona o nó com menor distância ainda não visitado
        minDist = inf;
        u = -1;
        for j = 1:n
            if ~visited(j) && dist(j) < minDist
                minDist = dist(j);
                u = j;
            end
        end
        
        % Se não houver mais nós acessíveis, saia do loop
        if u == -1
            break;
        end
        
        visited(u) = true; % Marca o nó como visitado
        
        % Relaxamento das arestas
        for v = 1:n
            if ~visited(v) && graph(u, v) ~= inf
                alt = dist(u) + graph(u, v);
                if alt < dist(v)
                    dist(v) = alt;
                    pred(v) = u;
                end
            end
        end
    end
end

% Reconstrução do caminho
function path = reconstruct_path(pred, startIdx, endIdx)
    path = [];
    currentNode = endIdx;
    while ~isnan(currentNode)
        path = [currentNode, path];
        if currentNode == startIdx
            break;
        end
        currentNode = pred(currentNode);
    end
end
