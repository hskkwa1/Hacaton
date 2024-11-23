function lissajous_interactive()
    % Parameters
    A_x = 1;      
    A_y = 1;          
    f_x = 3;          
    f_y = 2;          
    delta = pi/2;     
    t_max = 2*pi;     
    t = linspace(0, t_max, 1000); % Time
    dt = 0.01;        % Default step time
    signalTypeX = 'sine'; % Type of singal for X (default sine)
    signalTypeY = 'sine'; % Type of singal for Y (default sine)

    % Creating figure
    hFig = figure('Name', 'Interactive Lissajous Curves', 'NumberTitle', 'off', ...
                  'Position', [100, 100, 1000, 600]);

    % Axes for 2D curve
    hAxes2D = axes('Parent', hFig, 'Position', [0.1, 0.3, 0.35, 0.6]);
    grid(hAxes2D, 'on');
    axis(hAxes2D, 'equal');
    xlabel(hAxes2D, 'X');
    ylabel(hAxes2D, 'Y');
    title(hAxes2D, '2D Lissajous Curves');
    xlim(hAxes2D, [-A_x-1, A_x+1]);
    ylim(hAxes2D, [-A_y-1, A_y+1]);

    % Axes for 2D curve
    hAxes3D = axes('Parent', hFig, 'Position', [0.55, 0.3, 0.35, 0.6]);
    grid(hAxes3D, 'on');
    xlabel(hAxes3D, 'X');
    ylabel(hAxes3D, 'Y');
    zlabel(hAxes3D, 'Z');
    title(hAxes3D, '3D Lissajous Curves');
    xlim(hAxes3D, [-A_x-1, A_x+1]);
    ylim(hAxes3D, [-A_y-1, A_y+1]);
    zlim(hAxes3D, [0, t_max]);

    % Sliders for parameters
    uicontrol('Style', 'text', 'Position', [50, 250, 100, 20], 'String', 'Amplitude X');
    sliderAx = uicontrol('Style', 'slider', 'Min', 0, 'Max', 3, 'Value', A_x, ...
                         'Position', [150, 250, 120, 20], 'Callback', @update_plot);

    uicontrol('Style', 'text', 'Position', [50, 200, 100, 20], 'String', 'Amplitude Y');
    sliderAy = uicontrol('Style', 'slider', 'Min', 0, 'Max', 3, 'Value', A_y, ...
                         'Position', [150, 200, 120, 20], 'Callback', @update_plot);

    uicontrol('Style', 'text', 'Position', [50, 150, 100, 20], 'String', 'Frequency X');
    sliderFx = uicontrol('Style', 'slider', 'Min', 1, 'Max', 10, 'Value', f_x, ...
                         'Position', [150, 150, 120, 20], 'Callback', @update_plot);

    uicontrol('Style', 'text', 'Position', [50, 100, 100, 20], 'String', 'Frequency Y');
    sliderFy = uicontrol('Style', 'slider', 'Min', 1, 'Max', 10, 'Value', f_y, ...
                         'Position', [150, 100, 120, 20], 'Callback', @update_plot);

    uicontrol('Style', 'text', 'Position', [50, 50, 100, 20], 'String', 'Phase');
    sliderDelta = uicontrol('Style', 'slider', 'Min', 0, 'Max', 2*pi, 'Value', delta, ...
                            'Position', [150, 50, 120, 20], 'Callback', @update_plot);

    % Slider for adjusting speed
    % uicontrol('Style', 'text', 'Position', [300, 50, 100, 20], 'String', 'Speed');
    % sliderSpeed = uicontrol('Style', 'slider', 'Min', 0.001, 'Max', 0.1, 'Value', dt, ...
    %                         'Position', [400, 50, 120, 20], 'Callback', @update_speed);

    % Dropdown for signal type for X
    uicontrol('Style', 'text', 'Position', [300, 200, 100, 20], 'String', 'Singal X');
    popupSignalX = uicontrol('Style', 'popupmenu', 'String', {'Sine', 'Triangle'}, ...
                             'Position', [400, 200, 120, 20], 'Callback', @update_signal);

    % Dropdown for signal type for Y
    uicontrol('Style', 'text', 'Position', [300, 160, 100, 20], 'String', 'Signal Y');
    popupSignalY = uicontrol('Style', 'popupmenu', 'String', {'Sine', 'Triangle'}, ...
                             'Position', [400, 160, 120, 20], 'Callback', @update_signal);

    % Button to start animation
    uicontrol('Style', 'pushbutton', 'String', 'Start animation', ...
              'Position', [800, 100, 120, 30], 'Callback', @start_animation);
    
    % Button to stop animation
    stopButton = uicontrol('Style', 'pushbutton', 'String', 'Stop animation', ...
              'Position', [800, 50, 120, 30], 'Callback', @stop_animation);
    
    % Variable flag for animation control
    isAnimating = false;

    % Initial plot of the curve
    update_plot();
    
    % Function to update the plot
    function update_plot(~, ~)
        % Get slider values
        A_x = sliderAx.Value;
        A_y = sliderAy.Value;
        f_x = sliderFx.Value;
        f_y = sliderFy.Value;
        delta = sliderDelta.Value;

        % Select signal type
        if popupSignalX.Value == 1
            signalTypeX = 'sine';
        else
            signalTypeX = 'triangle';
        end
        if popupSignalY.Value == 1
            signalTypeY = 'sine';
        else
            signalTypeY = 'triangle';
        end

        % Lissajous equations supporting triangle signals
        x = generate_signal(signalTypeX, A_x, f_x, t, delta);
        y = generate_signal(signalTypeY, A_y, f_y, t, delta);
        z = t;  % Use time as the Z coordinate for the 3D curve

        % Plot 2D curve
        plot(hAxes2D, x, y, 'b', 'LineWidth', 2);
        hold(hAxes2D, 'on');
        plot(hAxes2D, A_x * sin(2 * pi * f_x * 0), A_y * sin(2 * pi * f_y * 0 + delta), 'ro', 'MarkerFaceColor', 'r');
        hold(hAxes2D, 'off');
        title(hAxes2D, sprintf('2D Lissajous Curve: A_x=%.2f, A_y=%.2f, f_x=%.2f, f_y=%.2f, \\delta=%.2f', A_x, A_y, f_x, f_y, delta));
        xlim(hAxes2D, [-A_x-1, A_x+1]);
        ylim(hAxes2D, [-A_y-1, A_y+1]);
        
        % Plot 3D curve
        plot3(hAxes3D, x, y, z, 'b', 'LineWidth', 2);
        hold(hAxes3D, 'on');
        plot3(hAxes3D, A_x * sin(2 * pi * f_x * 0), A_y * sin(2 * pi * f_y * 0 + delta), 0, 'ro', 'MarkerFaceColor', 'r');
        hold(hAxes3D, 'off');
        title(hAxes3D, sprintf('3D Lissajous Curve: A_x=%.2f, A_y=%.2f, f_x=%.2f, f_y=%.2f, \\delta=%.2f', A_x, A_y, f_x, f_y, delta));
        xlim(hAxes3D, [-A_x-1, A_x+1]);
        ylim(hAxes3D, [-A_y-1, A_y+1]);
        zlim(hAxes3D, [0, t_max]);
    end

    % Function to generate signals
    function signal = generate_signal(type, A, f, t, delta)
        switch type
            case 'sine'
                signal = A * sin(2 * pi * f * t + delta);
            case 'triangle'
                signal = A * sawtooth(2 * pi * f * t, 0.5); % Triangle wave
        end
    end

    % % Update animation speed
    % function update_speed(~, ~)
    %     dt = sliderSpeed.Value;
    % end

    % Signal type update function
    function update_signal(~, ~)
        update_plot(); % Redraw graphs when the signal changes
    end

    % Start animation function
    function start_animation(~, ~)
        isAnimating = true;
        t_animate = 0;
        x_data = [];
        y_data = [];
        maxTime = 10; % Maximum animation time in seconds
        % dt = sliderSpeed.Value;

        while isAnimating && t_animate < maxTime
            t_animate = t_animate + dt;
            x = generate_signal(signalTypeX, A_x, f_x, t_animate, delta);
            y = generate_signal(signalTypeY, A_y, f_y, t_animate, delta);

            % Accumulating data for animation
            x_data = [x_data, x];
            y_data = [y_data, y];

            % Real-time curve drawing
            plot(hAxes2D, x_data, y_data, 'b', 'LineWidth', 2);
            hold(hAxes2D, 'on');
            plot(hAxes2D, x, y, 'ro', 'MarkerFaceColor', 'r'); % Current point, marker
            hold(hAxes2D, 'off');

            % Для 3D графика
            z_data = linspace(0, t_animate, length(x_data));
            plot3(hAxes3D, x_data, y_data, z_data, 'b', 'LineWidth', 2);
            hold(hAxes3D, 'on');
            plot3(hAxes3D, x, y, t_animate, 'ro', 'MarkerFaceColor', 'r'); % Current point
            hold(hAxes3D, 'off');

            pause(dt);
        end

        % If the animation has finished, you can reset the data or perform other actions
        if ~isAnimating
            x_data = []; % Reset data
            y_data = [];
        end
    end

    % Stop animation
    function stop_animation(~, ~)
        isAnimating = false;
    end
end